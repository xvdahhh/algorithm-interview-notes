/* Browser smoke checks. Pass the installed playwright package path as argv[2]. */
const { chromium } = require(process.argv[2] || 'playwright');
const fs = require('node:fs');
const path = require('node:path');
const { pathToFileURL } = require('node:url');
const assert = require('node:assert/strict');
const root = path.resolve(__dirname, '..');
const chapters = JSON.parse(fs.readFileSync(path.join(__dirname, 'chapters.json'), 'utf8'));
(async () => {
  const browser = await chromium.launch({
    executablePath: 'C:/Program Files/Google/Chrome/Application/chrome.exe',
    headless: true,
  });
  try {
    const page = await browser.newPage({ viewport: { width: 1440, height: 1000 } });
    const errors = [];
    page.on('pageerror', error => errors.push(error.message));
    const open = relative => page.goto(pathToFileURL(path.join(root, relative)).href);
    const out = path.join(__dirname, 'qa');
    fs.mkdirSync(out, { recursive: true });
    await open('index.html');
    assert.equal(await page.locator('.chapter-card').count(), 15);
    await page.locator('#chapter-search').fill('LRU');
    assert.ok(await page.locator('.chapter-card:visible').count() >= 1);
    assert.ok(await page.locator('.chapter-card:visible').count() < 15);
    await page.locator('#chapter-search').fill('unmatchablexyz');
    assert.equal(await page.locator('.chapter-card:visible').count(), 0);
    assert.ok(await page.locator('#empty-search').isVisible());
    await page.locator('#chapter-search').fill('');
    await page.screenshot({ path: path.join(out, 'desktop-home.png') });
    await open(path.join(chapters[11].dir, 'index.html'));
    const checkbox = page.locator('[data-progress]').first();
    await checkbox.check();
    await page.reload();
    assert.ok(await checkbox.isChecked());
    await checkbox.uncheck();
    await page.locator('.lesson .copy').first().click();
    await page.waitForFunction(() => document.querySelector('.toast').textContent.includes('代码已'));
    await page.evaluate(() => window.scrollTo(0, 0));
    await page.screenshot({ path: path.join(out, 'desktop-chapter.png') });
    await page.setViewportSize({ width: 390, height: 844 });
    await page.locator('.nav-toggle').click();
    assert.equal(await page.locator('.nav-toggle').getAttribute('aria-expanded'), 'true');
    await page.keyboard.press('Escape');
    assert.equal(await page.locator('.nav-toggle').getAttribute('aria-expanded'), 'false');
    for (const c of chapters) {
      await open(path.join(c.dir, 'index.html'));
      assert.equal(await page.locator('.lesson').count(), c.sections.length);
      const overflow = await page.evaluate(() => document.documentElement.scrollWidth > innerWidth);
      assert.equal(overflow, false, 'page overflow: ' + c.dir);
    }
    await open(path.join(chapters[11].dir, 'index.html'));
    await page.screenshot({ path: path.join(out, 'mobile-chapter.png') });
    await open('index.html');
    assert.equal(await page.evaluate(() => document.documentElement.scrollWidth > innerWidth), false);
    await page.screenshot({ path: path.join(out, 'mobile-home.png') });
    assert.deepEqual(errors, []);
    console.log('PASS: all 16 pages open offline; search, copy, progress, mobile menu and mobile width checks pass.');
    console.log('Screenshots: ' + out);
  } finally { await browser.close(); }
})().catch(error => { console.error(error); process.exitCode = 1; });
