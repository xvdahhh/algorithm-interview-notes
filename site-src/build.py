"""Build the offline HTML handbook and C++ examples. Run with Python 3.11+."""
from pathlib import Path
import html
import json
import re

ROOT = Path(__file__).resolve().parent.parent
CHAPTERS = json.loads((ROOT / 'site-src' / 'chapters.json').read_text(encoding='utf-8'))
HEADER = '''#include <algorithm>
#include <array>
#include <cassert>
#include <climits>
#include <cstdint>
#include <cstdlib>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <numeric>
#include <optional>
#include <queue>
#include <random>
#include <stack>
#include <stdexcept>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
'''

def esc(s):
    return html.escape(str(s), quote=True)

def highlight(code):
    pattern = r'//[^\n]*|"(?:\\.|[^"\\])*"|\b(?:int|long|bool|void|char|double|auto|const|if|else|for|while|return|class|struct|public|private|explicit|using|namespace|true|false|nullptr|throw|sizeof)\b|\b\d+(?:LL|ULL)?\b'
    parts = []
    prev = 0
    for m in re.finditer(pattern, code):
        parts.append(esc(code[prev:m.start()]))
        token = m.group()
        cls = 'comment' if token.startswith('//') else 'string' if token.startswith('"') else 'number' if token[0].isdigit() else 'keyword'
        parts.append(f'<span class="{cls}">{esc(token)}</span>')
        prev = m.end()
    parts.append(esc(code[prev:]))
    return ''.join(parts)

def codeblock(code, label='C++17', download=None):
    dl = f'<a href="{esc(download)}" download>下载 .cpp</a>' if download else ''
    return f'<div class="codebox"><div class="codebar"><span>{label}</span><div>{dl}<button type="button" class="copy">复制代码</button></div></div><pre tabindex="0" aria-label="{label} 代码"><code>{highlight(code)}</code></pre></div>'

def render_answers(items):
    return '<dl class="answer-list">' + ''.join(
        f'<div><dt>{esc(item["question"])}</dt><dd>'
        + ''.join(f'<p>{esc(p)}</p>' for p in item['answer'])
        + '</dd></div>' for item in items) + '</dl>'

def render_blocks(blocks, examples, anchor_prefix):
    """Render optional chapter deep dives from structured, escaped content."""
    output = []
    for index, block in enumerate(blocks, 1):
        anchor = f'{anchor_prefix}-{index}'
        output.append(f'<div class="deep-block" id="{anchor}"><h3>{esc(block["title"])}</h3>')
        output.extend(f'<p>{esc(p)}</p>' for p in block.get('paragraphs', []))
        if block['type'] == 'table':
            head = ''.join(f'<th scope="col">{esc(v)}</th>' for v in block['columns'])
            rows = ''.join('<tr>' + ''.join(f'<td>{esc(v)}</td>' for v in row) + '</tr>' for row in block['rows'])
            output.append(f'<p class="table-hint">窄屏下可左右滑动表格，查看完整内容。</p><div class="study-table" tabindex="0" role="region" aria-label="{esc(block["title"])}"><table><thead><tr>{head}</tr></thead><tbody>{rows}</tbody></table></div>')
        elif block['type'] == 'code':
            filename = block['file']
            if Path(filename).name != filename or not filename.endswith('.cpp'):
                raise ValueError(f'Invalid example filename: {filename}')
            (examples / filename).write_text(HEADER + '\n' + block['code'] + '\n', encoding='utf-8')
            output.append(codeblock(block['code'], download='examples/' + filename))
        elif block['type'] == 'qa':
            output.append(render_answers(block['items']))
        elif block['type'] != 'text':
            raise ValueError(f'Unknown block type: {block["type"]}')
        output.append('</div>')
    return ''.join(output)

def shell(title, body, current=None, toc=''):
    prefix = '' if current is None else '../'
    nav = ''.join(f'<a class="chapter-link{" active" if i==current else ""}" {"aria-current=page" if i==current else ""} href="{prefix}{esc(c["dir"])}/index.html"><span>{i+1:02d}</span>{esc(c["title"])}</a>' for i,c in enumerate(CHAPTERS))
    return f'''<!doctype html>
<html lang="zh-CN"><head><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1">
<meta name="description" content="秋招算法手撕学习讲义：知识推导、经典考点、C++17 示例与面试训练。">
<title>{esc(title)} · 算法手撕讲义</title><link rel="stylesheet" href="{prefix}assets/style.css"><script src="{prefix}assets/app.js" defer></script></head>
<body><a class="skip" href="#main">跳到正文</a><header class="topbar"><a class="brand" href="{prefix}index.html"><span class="brand-mark">a[i]</span><span>算法手撕讲义<small>秋招学习工作区 / C++17</small></span></a><button type="button" class="nav-toggle" aria-expanded="false" aria-controls="chapter-nav">章节目录</button><a class="home-link" href="{prefix}index.html">全部章节 ↗</a></header>
<div class="layout"><aside class="sidebar" id="chapter-nav" aria-label="章节导航"><p class="rail-label">LEARNING PATH · 学习路径</p><nav>{nav}</nav><div class="sidebar-note">读懂不变量，独立写代码。<br>共 15 章 · 63 个小节<br>无需联网，浏览器直接打开。</div></aside><main id="main">{body}<footer>秋招算法学习讲义 · C++17<br>例题编号供检索；难度与覆盖范围按学习顺序组织。</footer></main><aside class="toc" aria-label="本页目录">{toc}</aside></div><div class="toast" role="status" aria-live="polite"></div></body></html>'''

def build():
    for i,c in enumerate(CHAPTERS):
        directory = ROOT / c['dir']
        examples = directory / 'examples'
        examples.mkdir(exist_ok=True, parents=True)
        detail_path = directory / 'detail.json'
        detail = json.loads(detail_path.read_text(encoding='utf-8')) if detail_path.exists() else {}
        toc = '<p class="rail-label">本章小节</p>' + ''.join(f'<a href="#s{j+1}"><span>{j+1:02d}</span>{esc(s[0])}</a>' for j,s in enumerate(c['sections']))
        if detail:
            toc += '<a href="#chapter-review"><span>练</span>综合例题与自测答案</a>'
        body = f'<header class="chapter-header"><p class="eyebrow">CHAPTER {i+1:02d} / 15</p><h1>{esc(c["title"])}</h1><p class="lead">{esc(c["intro"])}</p><div class="chapter-meta"><span>{len(c["sections"])} 个小节</span><span>C++17 示例</span><a href="README.md">原始知识摘要 ↗</a></div></header>'
        body += '<div class="reading-guide"><strong>本章怎么学</strong><p>先读原理与不变量，遮住代码手推例子，再独立实现。最后用面试追问检查理解，按练习条目做变式。</p></div>'
        if detail:
            body += '<div class="deep-intro">' + render_blocks(detail.get('intro', []), examples, 'guide') + '</div>'
            body += '<nav class="chapter-outline" aria-label="本章阅读路线"><strong>直接跳到</strong>'
            body += ''.join(f'<a href="#s{j+1}">{j+1:02d} {esc(s[0])}</a>' for j,s in enumerate(c['sections']))
            body += '<a href="#chapter-review">综合例题与自测答案</a></nav>'
        body += '<details class="environment"><summary>代码使用说明与通用头文件</summary><p>示例统一采用 C++17。页面展示核心函数或类，下载的 .cpp 已包含以下头文件，可独立编译。不同小节可能重用类型名，应分别编译；含 main 的示例可直接运行，其余需自行补充调用与测试。复制按钮复制当前代码块。</p>'
        body += codeblock(HEADER) + '<p>检查单个示例：<code>g++ -std=c++17 -Wall -Wextra -c sample.cpp</code>。这只检查编译；验证结果还需要调用函数并覆盖边界输入。代码按题目约束编写，各节明确其适用前提。</p></details>'
        for j,s in enumerate(c['sections']):
            title,concept,reason,example,code,cost,pitfall,question,practice = s
            expansion = detail.get('sections', {}).get(str(j+1), {})
            filename=f'{j+1:02d}.cpp'
            (examples/filename).write_text(HEADER+'\n'+code+'\n',encoding='utf-8')
            body += f'''<section class="lesson" id="s{j+1}"><div class="lesson-heading"><span class="lesson-number">{i+1:02d}.{j+1:02d}</span><h2>{esc(title)}</h2></div>
<h3>知识与适用场景</h3><p>{esc(concept)}</p>'''
            body += render_blocks(expansion.get('before', []), examples, f's{j+1}-before')
            body += f'''<div class="invariant"><span>推导 / 不变量</span><p>{esc(reason)}</p></div>
<h3>手推一个例子</h3><p>{esc(example)}</p>{codeblock(code,download='examples/'+filename)}
<dl class="analysis-grid"><div><dt>复杂度</dt><dd>{esc(cost)}</dd></div><div><dt>易错点与边界</dt><dd>{esc(pitfall)}</dd></div></dl>
'''
            body += render_blocks(expansion.get('after', []), examples, f's{j+1}-after')
            body += f'<div class="practice"><h3>经典考点与练习</h3><p>{esc(practice)}</p>'
            if expansion.get('answers'):
                body += '<h3>面试追问：关键点完整解答</h3>' + render_answers(expansion['answers'])
            else:
                body += f'<details><summary>面试官可能继续问什么？</summary><p>{esc(question)}</p><p class="muted">先用自己的话回答，再回到本节的前提、不变量和边界检查论证。</p></details>'
            body += f'</div>\n<label class="learned"><input type="checkbox" data-progress="{i+1:02d}-{j+1:02d}">我能独立实现，并解释正确性与边界</label></section>'
        if detail.get('outro'):
            body += '<section class="chapter-review" id="chapter-review"><p class="eyebrow">PRACTICE / 把本章方法用起来</p><h2>综合例题与章末自测</h2>'
            body += render_blocks(detail['outro'], examples, 'review') + '</section>'
        prev = f'<a href="../{esc(CHAPTERS[i-1]["dir"])}/index.html"><small>上一章</small>← {esc(CHAPTERS[i-1]["title"])}</a>' if i else '<a href="../index.html"><small>回到起点</small>← 全部章节</a>'
        nxt = f'<a href="../{esc(CHAPTERS[i+1]["dir"])}/index.html"><small>下一章</small>{esc(CHAPTERS[i+1]["title"])} →</a>' if i+1<len(CHAPTERS) else '<a href="../index.html"><small>开始复习</small>回到学习目录 →</a>'
        body += f'<nav class="chapter-pager" aria-label="相邻章节">{prev}{nxt}</nav>'
        (directory/'index.html').write_text(shell(c['title'],body,i,toc),encoding='utf-8')
    cards = ''
    for i,c in enumerate(CHAPTERS):
        search = ' '.join([c['title']]+[s[0]+' '+s[8] for s in c['sections']])
        topics = ''.join(f'<li>{esc(s[0])}</li>' for s in c['sections'])
        cards += f'<article class="chapter-card" data-search="{esc(search.lower())}"><div class="card-top"><span class="card-number">{i+1:02d}</span><span>{len(c["sections"])} 小节</span></div><h2><a href="{esc(c["dir"])}/index.html">{esc(c["title"])}</a></h2><p>{esc(c["intro"])}</p><ul>{topics}</ul><a class="read-link" href="{esc(c["dir"])}/index.html">进入本章 <span>→</span></a></article>'
    body = f'''<header class="home-header"><p class="eyebrow">ALGORITHM FIELD NOTES / 秋招手撕</p><h1>从“看懂题解”<br>走到“独立写出”。</h1><p class="lead">沿着 15 章学习路径，掌握常用结构、算法推导与面试表达。每节都有适用场景、手推过程、C++ 示例和经典练习。</p></header>
<div class="method-strip"><div><span>01 理解</span><p>找到不变量或状态定义</p></div><div><span>02 实现</span><p>遮住示例，自己写一遍</p></div><div><span>03 验证</span><p>边界、复杂度、反例</p></div></div>
<section class="overview" aria-labelledby="directory-heading"><div class="directory-header"><h2 id="directory-heading">章节目录</h2><span id="progress-count">63 个小节，按自己的节奏学习</span></div><label class="search-label" for="chapter-search">查找知识点或经典题目</label><input type="search" id="chapter-search" placeholder="例如：二分、背包、LRU、142" autocomplete="off"><p id="search-status" class="muted" role="status">显示全部 15 章</p><div class="cards">{cards}</div><p id="empty-search" hidden>没有匹配的章节。试试算法名称、数据结构或题目编号。</p></section>
<section class="reading-guide"><strong>学习顺序与使用约定</strong><p>第 1–6 章打基础，第 7–10 章学习树与搜索，第 11–12 章攻克贪心和动态规划，第 13–14 章按需进阶，第 15 章安排训练与模拟。页面中的掌握勾选会在浏览器允许时保存在本地；它记录自评，不代表题目已通过测试。</p><p>所有文件均可离线阅读。C++ 示例按小节独立提供，点击“下载 .cpp”可获得带标准头文件的源文件。</p></section>'''
    (ROOT/'index.html').write_text(shell('学习目录',body),encoding='utf-8')
    example_count = sum(len(list((ROOT / c['dir'] / 'examples').glob('*.cpp'))) for c in CHAPTERS)
    print(f'Generated {len(CHAPTERS)+1} HTML pages with {example_count} C++ examples (including chapter deep dives).')

if __name__ == '__main__':
    build()
