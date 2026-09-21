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
    // Chapter 1 deep dive: answers remain visible and wide tables stay scrollable.
    await open(path.join(chapters[0].dir, 'index.html'));
    assert.equal(await page.locator('.answer-list dt').count(), 29);
    assert.equal(await page.locator('a[download][href*="detail-"]').count(), 7);
    assert.equal(await page.locator('.chapter-outline a').count(), 5);
    await page.setViewportSize({ width: 1440, height: 1000 });
    await page.screenshot({ path: path.join(out, 'chapter01-desktop.png') });
    await page.locator('#s3-before-2').scrollIntoViewIfNeeded();
    await page.screenshot({ path: path.join(out, 'chapter01-proof.png') });
    for (const width of [390, 320]) {
      await page.setViewportSize({ width, height: 844 });
      assert.equal(await page.evaluate(() => document.documentElement.scrollWidth > innerWidth), false);
      const table = page.locator('.study-table').first();
      await table.scrollIntoViewIfNeeded();
      assert.ok(await table.evaluate(el => el.scrollWidth > el.clientWidth));
    }
    await page.setViewportSize({ width: 390, height: 844 });
    await page.locator('#s1-before-2').scrollIntoViewIfNeeded();
    await page.screenshot({ path: path.join(out, 'chapter01-mobile-table.png') });
    await page.locator('.chapter-review .answer-list').scrollIntoViewIfNeeded();
    assert.ok(await page.locator('.chapter-review .answer-list dd').first().isVisible());
    await page.screenshot({ path: path.join(out, 'chapter01-mobile-answers.png') });
    // Chapter 2: proof tables, answer text, code copying and small screens.
    await open(path.join(chapters[1].dir, 'index.html'));
    assert.equal(await page.locator('.answer-list dt').count(), 34);
    assert.equal(await page.locator('a[download][href*="detail-"]').count(), 16);
    assert.equal(await page.locator('.study-table').count(), 10);
    assert.equal(await page.locator('.chapter-outline a').count(), 5);
    await page.setViewportSize({ width: 1440, height: 1000 });
    await page.screenshot({ path: path.join(out, 'chapter02-desktop.png') });
    await page.locator('#s2-before-6').scrollIntoViewIfNeeded();
    await page.screenshot({ path: path.join(out, 'chapter02-window-proof.png') });
    const extraExample = page.locator('.codebox').filter({
      has: page.locator('a[href="examples/detail-min-window.cpp"]')
    });
    await extraExample.locator('.copy').click();
    await page.waitForFunction(() => document.querySelector('.toast').textContent.includes('代码已'));
    for (const width of [390, 320]) {
      await page.setViewportSize({ width, height: 844 });
      assert.equal(await page.evaluate(() => document.documentElement.scrollWidth > innerWidth), false);
      const table = page.locator('.study-table').first();
      await table.scrollIntoViewIfNeeded();
      assert.ok(await table.evaluate(el => el.scrollWidth > el.clientWidth));
    }
    await page.setViewportSize({ width: 390, height: 844 });
    await page.locator('#s3-before-2').scrollIntoViewIfNeeded();
    await page.screenshot({ path: path.join(out, 'chapter02-mobile-prefix.png') });
    await page.locator('#s4 .answer-list').scrollIntoViewIfNeeded();
    assert.ok(await page.locator('#s4 .answer-list dd').first().isVisible());
    await page.screenshot({ path: path.join(out, 'chapter02-mobile-answers.png') });
    // Chapter 3: identity-oriented explanations, pointer traces and downloads.
    await open(path.join(chapters[2].dir, 'index.html'));
    assert.equal(await page.locator('.answer-list dt').count(), 34);
    assert.equal(await page.locator('a[download][href*="detail-"]').count(), 16);
    assert.equal(await page.locator('.study-table').count(), 10);
    assert.equal(await page.locator('.chapter-outline a').count(), 5);
    await page.setViewportSize({ width: 1440, height: 1000 });
    await page.screenshot({ path: path.join(out, 'chapter03-desktop.png') });
    await page.locator('#s3-before-7').scrollIntoViewIfNeeded();
    await page.screenshot({ path: path.join(out, 'chapter03-cycle-proof.png') });
    const linkedExample = page.locator('.codebox').filter({
      has: page.locator('a[href="examples/detail-reverse-k-group.cpp"]')
    });
    await linkedExample.locator('.copy').click();
    await page.waitForFunction(() => document.querySelector('.toast').textContent.includes('代码已'));
    for (const width of [390, 320]) {
      await page.setViewportSize({ width, height: 844 });
      assert.equal(await page.evaluate(() => document.documentElement.scrollWidth > innerWidth), false);
      const table = page.locator('.study-table').first();
      await table.scrollIntoViewIfNeeded();
      assert.ok(await table.evaluate(el => el.scrollWidth > el.clientWidth));
    }
    await page.setViewportSize({ width: 390, height: 844 });
    await page.locator('#s2-before-2').scrollIntoViewIfNeeded();
    await page.screenshot({ path: path.join(out, 'chapter03-mobile-reversal.png') });
    await page.locator('#s4 .answer-list').scrollIntoViewIfNeeded();
    assert.ok(await page.locator('#s4 .answer-list dd').first().isVisible());
    await page.screenshot({ path: path.join(out, 'chapter03-mobile-answers.png') });
    // Chapter 4: stack invariants, monotonic boundaries and amortized analysis.
    await open(path.join(chapters[3].dir, 'index.html'));
    assert.equal(await page.locator('.answer-list dt').count(), 32);
    assert.equal(await page.locator('a[download][href*="detail-"]').count(), 14);
    assert.equal(await page.locator('.study-table').count(), 10);
    assert.equal(await page.locator('.chapter-outline a').count(), 5);
    await page.setViewportSize({ width: 1440, height: 1000 });
    await page.screenshot({ path: path.join(out, 'chapter04-desktop.png') });
    await page.locator('#s2-after-3').scrollIntoViewIfNeeded();
    await page.screenshot({ path: path.join(out, 'chapter04-histogram.png') });
    const monotonicExample = page.locator('.codebox').filter({
      has: page.locator('a[href="examples/detail-shortest-subarray.cpp"]')
    });
    await monotonicExample.locator('.copy').click();
    await page.waitForFunction(() => document.querySelector('.toast').textContent.includes('代码已'));
    for (const width of [390, 320]) {
      await page.setViewportSize({ width, height: 844 });
      assert.equal(await page.evaluate(() => document.documentElement.scrollWidth > innerWidth), false);
      const table = page.locator('.study-table').first();
      await table.scrollIntoViewIfNeeded();
      assert.ok(await table.evaluate(el => el.scrollWidth > el.clientWidth));
    }
    await page.setViewportSize({ width: 390, height: 844 });
    await page.locator('#s3-after-5').scrollIntoViewIfNeeded();
    await page.screenshot({ path: path.join(out, 'chapter04-mobile-prefix.png') });
    await page.locator('#s4 .answer-list').scrollIntoViewIfNeeded();
    assert.ok(await page.locator('#s4 .answer-list dd').first().isVisible());
    await page.screenshot({ path: path.join(out, 'chapter04-mobile-answers.png') });
    // Chapter 5: complete hash states, bit boundaries and subset enumeration.
    await open(path.join(chapters[4].dir, 'index.html'));
    assert.equal(await page.locator('.answer-list dt').count(), 32);
    assert.equal(await page.locator('a[download][href*="detail-"]').count(), 15);
    assert.equal(await page.locator('.study-table').count(), 10);
    assert.equal(await page.locator('.chapter-outline a').count(), 5);
    await page.setViewportSize({ width: 1440, height: 1000 });
    await page.screenshot({ path: path.join(out, 'chapter05-desktop.png') });
    await page.locator('#s1-after-4').scrollIntoViewIfNeeded();
    await page.screenshot({ path: path.join(out, 'chapter05-prefix-count.png') });
    const bitExample = page.locator('.codebox').filter({
      has: page.locator('a[href="examples/detail-two-singles.cpp"]')
    });
    await bitExample.locator('.copy').click();
    await page.waitForFunction(() => document.querySelector('.toast').textContent.includes('代码已'));
    for (const width of [390, 320]) {
      await page.setViewportSize({ width, height: 844 });
      assert.equal(await page.evaluate(() => document.documentElement.scrollWidth > innerWidth), false);
      const table = page.locator('.study-table').first();
      await table.scrollIntoViewIfNeeded();
      assert.ok(await table.evaluate(el => el.scrollWidth > el.clientWidth));
    }
    await page.setViewportSize({ width: 390, height: 844 });
    await page.locator('#s4-before-5').scrollIntoViewIfNeeded();
    await page.screenshot({ path: path.join(out, 'chapter05-mobile-submasks.png') });
    await page.locator('#s3 .answer-list').scrollIntoViewIfNeeded();
    assert.ok(await page.locator('#s3 .answer-list dd').first().isVisible());
    await page.screenshot({ path: path.join(out, 'chapter05-mobile-answers.png') });
    // Chapter 6: partition invariants, binary boundaries and answer searches.
    await open(path.join(chapters[5].dir, 'index.html'));
    assert.equal(await page.locator('.answer-list dt').count(), 32);
    assert.equal(await page.locator('a[download][href*="detail-"]').count(), 16);
    assert.equal(await page.locator('.study-table').count(), 10);
    assert.equal(await page.locator('.chapter-outline a').count(), 5);
    await page.setViewportSize({ width: 1440, height: 1000 });
    await page.screenshot({ path: path.join(out, 'chapter06-desktop.png') });
    await page.locator('#s2-before-2').scrollIntoViewIfNeeded();
    await page.screenshot({ path: path.join(out, 'chapter06-partition.png') });
    const searchExample = page.locator('.codebox').filter({
      has: page.locator('a[href="examples/detail-median-two-sorted.cpp"]')
    });
    await searchExample.locator('.copy').click();
    await page.waitForFunction(() => document.querySelector('.toast').textContent.includes('代码已'));
    for (const width of [390, 320]) {
      await page.setViewportSize({ width, height: 844 });
      assert.equal(await page.evaluate(() => document.documentElement.scrollWidth > innerWidth), false);
      const table = page.locator('.study-table').first();
      await table.scrollIntoViewIfNeeded();
      assert.ok(await table.evaluate(el => el.scrollWidth > el.clientWidth));
    }
    await page.setViewportSize({ width: 390, height: 844 });
    await page.locator('#s3-before-2').scrollIntoViewIfNeeded();
    await page.screenshot({ path: path.join(out, 'chapter06-mobile-boundary.png') });
    await page.locator('#s4 .answer-list').scrollIntoViewIfNeeded();
    assert.ok(await page.locator('#s4 .answer-list dd').first().isVisible());
    await page.screenshot({ path: path.join(out, 'chapter06-mobile-answers.png') });
    // Chapter 7: postorder reports, pointer identity and tree serialization.
    await open(path.join(chapters[6].dir, 'index.html'));
    assert.equal(await page.locator('.answer-list dt').count(), 32);
    assert.equal(await page.locator('a[download][href*="detail-"]').count(), 15);
    assert.equal(await page.locator('.study-table').count(), 10);
    assert.equal(await page.locator('.chapter-outline a').count(), 5);
    await page.setViewportSize({ width: 1440, height: 1000 });
    await page.screenshot({ path: path.join(out, 'chapter07-desktop.png') });
    await page.locator('#s2-before-2').scrollIntoViewIfNeeded();
    await page.screenshot({ path: path.join(out, 'chapter07-postorder.png') });
    const treeExample = page.locator('.codebox').filter({
      has: page.locator('a[href="examples/detail-lca-checked.cpp"]')
    });
    await treeExample.locator('.copy').click();
    await page.waitForFunction(() => document.querySelector('.toast').textContent.includes('代码已'));
    for (const width of [390, 320]) {
      await page.setViewportSize({ width, height: 844 });
      assert.equal(await page.evaluate(() => document.documentElement.scrollWidth > innerWidth), false);
      const table = page.locator('.study-table').first();
      await table.scrollIntoViewIfNeeded();
      assert.ok(await table.evaluate(el => el.scrollWidth > el.clientWidth));
    }
    await page.setViewportSize({ width: 390, height: 844 });
    await page.locator('#s2-after-6').scrollIntoViewIfNeeded();
    await page.screenshot({ path: path.join(out, 'chapter07-mobile-prefix.png') });
    await page.locator('#s4 .answer-list').scrollIntoViewIfNeeded();
    assert.ok(await page.locator('#s4 .answer-list dd').first().isVisible());
    await page.screenshot({ path: path.join(out, 'chapter07-mobile-answers.png') });
    // Chapter 8: heap ordering, candidate frontiers and median deletion.
    await open(path.join(chapters[7].dir, 'index.html'));
    assert.equal(await page.locator('.answer-list dt').count(), 32);
    assert.equal(await page.locator('a[download][href*="detail-"]').count(), 13);
    assert.equal(await page.locator('.study-table').count(), 10);
    assert.equal(await page.locator('.chapter-outline a').count(), 5);
    await page.setViewportSize({ width: 1440, height: 1000 });
    await page.screenshot({ path: path.join(out, 'chapter08-desktop.png') });
    await page.locator('#s1-after-1').scrollIntoViewIfNeeded();
    await page.screenshot({ path: path.join(out, 'chapter08-comparator.png') });
    const heapExample = page.locator('.codebox').filter({
      has: page.locator('a[href="examples/detail-sliding-median.cpp"]')
    });
    await heapExample.locator('.copy').click();
    await page.waitForFunction(() => document.querySelector('.toast').textContent.includes('代码已'));
    for (const width of [390, 320]) {
      await page.setViewportSize({ width, height: 844 });
      assert.equal(await page.evaluate(() => document.documentElement.scrollWidth > innerWidth), false);
      const table = page.locator('.study-table').first();
      await table.scrollIntoViewIfNeeded();
      assert.ok(await table.evaluate(el => el.scrollWidth > el.clientWidth));
    }
    await page.setViewportSize({ width: 390, height: 844 });
    await page.locator('#s3-before-2').scrollIntoViewIfNeeded();
    await page.screenshot({ path: path.join(out, 'chapter08-mobile-merge.png') });
    await page.locator('#s4 .answer-list').scrollIntoViewIfNeeded();
    assert.ok(await page.locator('#s4 .answer-list dd').first().isVisible());
    await page.screenshot({ path: path.join(out, 'chapter08-mobile-answers.png') });
    // Chapter 9: branching semantics, duplicate removal and rollback contracts.
    await open(path.join(chapters[8].dir, 'index.html'));
    assert.equal(await page.locator('.answer-list dt').count(), 32);
    assert.equal(await page.locator('a[download][href*="detail-"]').count(), 13);
    assert.equal(await page.locator('.study-table').count(), 10);
    assert.equal(await page.locator('.chapter-outline a').count(), 5);
    await page.setViewportSize({ width: 1440, height: 1000 });
    await page.screenshot({ path: path.join(out, 'chapter09-desktop.png') });
    await page.locator('#s2-before-2').scrollIntoViewIfNeeded();
    await page.screenshot({ path: path.join(out, 'chapter09-dedup.png') });
    const backtrackExample = page.locator('.codebox').filter({
      has: page.locator('a[href="examples/detail-word-search.cpp"]')
    });
    await backtrackExample.locator('.copy').click();
    await page.waitForFunction(() => document.querySelector('.toast').textContent.includes('代码已'));
    for (const width of [390, 320]) {
      await page.setViewportSize({ width, height: 844 });
      assert.equal(await page.evaluate(() => document.documentElement.scrollWidth > innerWidth), false);
      const table = page.locator('.study-table').first();
      await table.scrollIntoViewIfNeeded();
      assert.ok(await table.evaluate(el => el.scrollWidth > el.clientWidth));
    }
    await page.setViewportSize({ width: 390, height: 844 });
    await page.locator('#s3-after-4').scrollIntoViewIfNeeded();
    await page.screenshot({ path: path.join(out, 'chapter09-mobile-rollback.png') });
    await page.locator('#s4 .answer-list').scrollIntoViewIfNeeded();
    assert.ok(await page.locator('#s4 .answer-list dd').first().isVisible());
    await page.screenshot({ path: path.join(out, 'chapter09-mobile-answers.png') });
    // Chapter 10: graph models, negative-cycle scope and cut properties.
    await open(path.join(chapters[9].dir, 'index.html'));
    assert.equal(await page.locator('.answer-list dt').count(), 32);
    assert.equal(await page.locator('a[download][href*="detail-"]').count(), 14);
    assert.equal(await page.locator('.study-table').count(), 10);
    assert.equal(await page.locator('.chapter-outline a').count(), 6);
    await page.setViewportSize({ width: 1440, height: 1000 });
    await page.screenshot({ path: path.join(out, 'chapter10-desktop.png') });
    await page.locator('#s2-before-3').scrollIntoViewIfNeeded();
    await page.screenshot({ path: path.join(out, 'chapter10-cycles.png') });
    const graphExample = page.locator('.codebox').filter({
      has: page.locator('a[href="examples/detail-zero-one-bfs.cpp"]')
    });
    await graphExample.locator('.copy').click();
    await page.waitForFunction(() => document.querySelector('.toast').textContent.includes('代码已'));
    for (const width of [390, 320]) {
      await page.setViewportSize({ width, height: 844 });
      assert.equal(await page.evaluate(() => document.documentElement.scrollWidth > innerWidth), false);
      const table = page.locator('.study-table').first();
      await table.scrollIntoViewIfNeeded();
      assert.ok(await table.evaluate(el => el.scrollWidth > el.clientWidth));
    }
    await page.setViewportSize({ width: 390, height: 844 });
    await page.locator('#s4-before-2').scrollIntoViewIfNeeded();
    await page.screenshot({ path: path.join(out, 'chapter10-mobile-negative-cycles.png') });
    await page.locator('#s5 .answer-list').scrollIntoViewIfNeeded();
    assert.ok(await page.locator('#s5 .answer-list dd').first().isVisible());
    await page.screenshot({ path: path.join(out, 'chapter10-mobile-answers.png') });
    assert.deepEqual(errors, []);
    console.log('PASS: all 16 pages open offline; search, copy, progress, mobile menu and mobile width checks pass.');
    console.log('Screenshots: ' + out);
  } finally { await browser.close(); }
})().catch(error => { console.error(error); process.exitCode = 1; });
