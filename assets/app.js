'use strict';
const toast = document.querySelector('.toast');
let toastTimer;
function notify(message) {
  toast.textContent = message;
  toast.classList.add('show');
  clearTimeout(toastTimer);
  toastTimer = setTimeout(() => toast.classList.remove('show'), 2400);
}
document.querySelectorAll('.copy').forEach(button => {
  button.addEventListener('click', async () => {
    const code = button.closest('.codebox').querySelector('code');
    const text = code.textContent;
    try {
      if (!navigator.clipboard) throw new Error('fallback');
      await navigator.clipboard.writeText(text);
      notify('代码已复制');
    } catch {
      const area = document.createElement('textarea');
      area.value = text;
      area.style.position = 'fixed';
      area.style.left = '-9999px';
      document.body.append(area);
      area.select();
      let copied = false;
      try { copied = document.execCommand('copy'); } catch {}
      area.remove();
      if (copied) notify('代码已复制');
      else {
        const range = document.createRange();
        range.selectNodeContents(code);
        const selection = window.getSelection();
        selection.removeAllRanges(); selection.addRange(range);
        notify('代码已选中，请按 Ctrl+C 或 ⌘C 复制');
      }
      button.focus();
    }
  });
});
const toggle = document.querySelector('.nav-toggle');
const navigation = document.querySelector('#chapter-nav');
function closeNavigation() {
  navigation.classList.remove('open');
  toggle.setAttribute('aria-expanded', 'false');
}
toggle.addEventListener('click', () => {
  const open = navigation.classList.toggle('open');
  toggle.setAttribute('aria-expanded', String(open));
});
document.addEventListener('keydown', e => {
  if (e.key === 'Escape' && navigation.classList.contains('open')) {
    closeNavigation(); toggle.focus();
  }
});
document.addEventListener('click', e => {
  if (!navigation.contains(e.target) && !toggle.contains(e.target)) closeNavigation();
});
const storageKey = 'algorithm-handbook-progress-v1';
let progress = {};
try {
  const saved = JSON.parse(localStorage.getItem(storageKey) || '{}');
  if (saved && typeof saved === 'object' && !Array.isArray(saved)) progress = saved;
} catch {}
document.querySelectorAll('[data-progress]').forEach(box => {
  box.checked = progress[box.dataset.progress] === true;
  box.addEventListener('change', () => {
    progress[box.dataset.progress] = box.checked;
    try { localStorage.setItem(storageKey, JSON.stringify(progress)); }
    catch { notify('当前浏览器无法保存进度，本次页面内仍可勾选'); }
  });
});
const count = document.querySelector('#progress-count');
if (count) {
  const completed = Object.values(progress).filter(x => x === true).length;
  count.textContent = `已自评掌握 ${completed} / 63 个小节`;
}
const search = document.querySelector('#chapter-search');
if (search) {
  search.addEventListener('input', () => {
    const tokens = search.value.trim().toLowerCase().split(/\s+/).filter(Boolean);
    let visible = 0;
    document.querySelectorAll('.chapter-card').forEach(card => {
      const match = tokens.every(t => card.dataset.search.includes(t));
      card.hidden = !match;
      if (match) ++visible;
    });
    document.querySelector('#search-status').textContent = `显示 ${visible} / 15 章`;
    document.querySelector('#empty-search').hidden = visible !== 0;
  });
}
if ('IntersectionObserver' in window) {
  const observer = new IntersectionObserver(entries => {
    for (const entry of entries) {
      if (!entry.isIntersecting) continue;
      document.querySelectorAll('.toc a').forEach(a => {
        a.classList.toggle('current', a.getAttribute('href') === '#' + entry.target.id);
      });
    }
  }, { rootMargin: '-100px 0px -65% 0px', threshold: 0 });
  document.querySelectorAll('.lesson').forEach(s => observer.observe(s));
}
