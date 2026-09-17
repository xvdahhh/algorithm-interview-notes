"""Check generated local links, anchors, section coverage, and example parity."""
from html.parser import HTMLParser
from pathlib import Path
from urllib.parse import unquote, urlsplit
import json

ROOT = Path(__file__).resolve().parent.parent

class Page(HTMLParser):
    def __init__(self, path):
        super().__init__()
        self.ids, self.links, self.lessons = set(), [], 0
        self.feed(path.read_text(encoding='utf-8'))
    def handle_starttag(self, tag, attrs):
        a = dict(attrs)
        if 'id' in a:
            assert a['id'] not in self.ids, f'duplicate id: {a["id"]}'
            self.ids.add(a['id'])
        for key in ('href', 'src'):
            if key in a:
                self.links.append(a[key])
        if tag == 'section' and a.get('class') == 'lesson':
            self.lessons += 1

pages = {p.resolve(): Page(p) for p in ROOT.rglob('*.html')}
links = 0
for p, page in pages.items():
    for link in page.links:
        url = urlsplit(link)
        if url.scheme or url.netloc:
            continue
        target = (p.parent / unquote(url.path)).resolve() if url.path else p
        assert target.exists(), f'broken link: {p.name} -> {link}'
        if url.fragment and target in pages:
            assert unquote(url.fragment) in pages[target].ids, f'bad anchor: {link}'
        links += 1
chapters = json.loads((ROOT/'site-src/chapters.json').read_text(encoding='utf-8'))
for c in chapters:
    path = ROOT/c['dir']
    assert pages[(path/'index.html').resolve()].lessons == len(c['sections'])
    for i,s in enumerate(c['sections']):
        assert len(s) == 9 and all(isinstance(v,str) and v.strip() for v in s)
        cpp = (path/'examples'/f'{i+1:02d}.cpp').read_text(encoding='utf-8')
        assert cpp.endswith(s[4]+'\n'), f'example differs: {c["dir"]}/{i+1}'
assert len(pages) == len(chapters)+1
print(f'PASS: {len(pages)} HTML pages, {sum(p.lessons for p in pages.values())} lessons, {links} local references; all C++ downloads match source.')
