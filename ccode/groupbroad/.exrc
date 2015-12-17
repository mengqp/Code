if &cp | set nocp | endif
let s:cpo_save=&cpo
set cpo&vim
inoremap <Nul> 
inoremap <expr> <Up> pumvisible() ? "\" : "\<Up>"
inoremap <expr> <S-Tab> pumvisible() ? "\" : "\<S-Tab>"
inoremap <expr> <Down> pumvisible() ? "\" : "\<Down>"
inoremap <silent> <Plug>NERDCommenterInsert  <BS>:call NERDComment('i', "insert")
inoremap <silent> <SNR>19_AutoPairsReturn =AutoPairsReturn()
nnoremap <silent>  :call repeat#wrap("\<C-R>",v:count)
nmap d :cs find d =expand("<cword>") "查找被这个函数调用的函数（们）
nmap i :cs find i =expand("<cfile>") "查找#include这个文件的文件（们）
nmap f :cs find f =expand("<cfile>") "查找这个文件
nmap e :cs find e =expand("<cword>") "查找这个egrep匹配模式
nmap t :cs find t =expand("<cword>") "查找这个字符串
nmap c :cs find c =expand("<cword>") "查找调用这个函数的函数
nmap g :cs find g =expand("<cword>") "查找定义
nmap s :cs find s =expand("<cword>") "查找C符号
nmap <silent> # <Plug>MarkSearchPrev
nmap <silent> * <Plug>MarkSearchNext
nnoremap ,d :YcmShowDetailedDiagnostic
map <silent> ,mm :ShowMarksPlaceMark
map <silent> ,ma :ShowMarksClearAll
map <silent> ,mh :ShowMarksClearMark
map <silent> ,mo :ShowMarksOn
map <silent> ,mt :ShowMarksToggle
nmap ,ca <Plug>NERDCommenterAltDelims
xmap ,cu <Plug>NERDCommenterUncomment
nmap ,cu <Plug>NERDCommenterUncomment
xmap ,cb <Plug>NERDCommenterAlignBoth
nmap ,cb <Plug>NERDCommenterAlignBoth
xmap ,cl <Plug>NERDCommenterAlignLeft
nmap ,cl <Plug>NERDCommenterAlignLeft
nmap ,cA <Plug>NERDCommenterAppend
xmap ,cy <Plug>NERDCommenterYank
nmap ,cy <Plug>NERDCommenterYank
xmap ,cs <Plug>NERDCommenterSexy
nmap ,cs <Plug>NERDCommenterSexy
xmap ,ci <Plug>NERDCommenterInvert
nmap ,ci <Plug>NERDCommenterInvert
nmap ,c$ <Plug>NERDCommenterToEOL
xmap ,cn <Plug>NERDCommenterNested
nmap ,cn <Plug>NERDCommenterNested
xmap ,cm <Plug>NERDCommenterMinimal
nmap ,cm <Plug>NERDCommenterMinimal
xmap ,c  <Plug>NERDCommenterToggle
nmap ,c  <Plug>NERDCommenterToggle
xmap ,cc <Plug>NERDCommenterComment
nmap ,cc <Plug>NERDCommenterComment
nmap <silent> ,? <Plug>MarkSearchAnyPrev
nmap <silent> ,/ <Plug>MarkSearchAnyNext
nmap <silent> ,# <Plug>MarkSearchCurrentPrev
nmap <silent> ,* <Plug>MarkSearchCurrentNext
nmap <silent> ,n <Plug>MarkClear
vmap <silent> ,r <Plug>MarkRegex
nmap <silent> ,r <Plug>MarkRegex
vmap <silent> ,m <Plug>MarkSet
nmap <silent> ,m <Plug>MarkSet
nmap ,ihn :IHN
nmap ,is :IHS:A
nmap ,ih :IHS
nnoremap <silent> ,q :QToggle
nnoremap <silent> ,l :LToggle
nmap <silent> ,mk :MarksBrowser 
nnoremap ,gg :YcmCompleter GoToDefinitionElseDeclaration
nmap ,gd :YcmDiags
nmap ,il :IndentLinesToggle
nmap ,man :Man 3 <cword>"
nnoremap <silent> . :call repeat#run(v:count)
map Q gq
nnoremap <silent> U :call repeat#wrap('U',v:count)
nmap cM :%s/\r$//g:noh<CR"
nmap cS :%s/\s\+$//g:noh     
nmap gx <Plug>NetrwBrowseX
nmap tb :Tagbar
nnoremap <silent> u :call repeat#wrap('u',v:count)
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#NetrwBrowseX(expand("<cWORD>"),0)
xnoremap <silent> <Plug>NERDCommenterUncomment :call NERDComment("x", "Uncomment")
nnoremap <silent> <Plug>NERDCommenterUncomment :call NERDComment("n", "Uncomment")
xnoremap <silent> <Plug>NERDCommenterAlignBoth :call NERDComment("x", "AlignBoth")
nnoremap <silent> <Plug>NERDCommenterAlignBoth :call NERDComment("n", "AlignBoth")
xnoremap <silent> <Plug>NERDCommenterAlignLeft :call NERDComment("x", "AlignLeft")
nnoremap <silent> <Plug>NERDCommenterAlignLeft :call NERDComment("n", "AlignLeft")
nnoremap <silent> <Plug>NERDCommenterAppend :call NERDComment("n", "Append")
xnoremap <silent> <Plug>NERDCommenterYank :call NERDComment("x", "Yank")
nnoremap <silent> <Plug>NERDCommenterYank :call NERDComment("n", "Yank")
xnoremap <silent> <Plug>NERDCommenterSexy :call NERDComment("x", "Sexy")
nnoremap <silent> <Plug>NERDCommenterSexy :call NERDComment("n", "Sexy")
xnoremap <silent> <Plug>NERDCommenterInvert :call NERDComment("x", "Invert")
nnoremap <silent> <Plug>NERDCommenterInvert :call NERDComment("n", "Invert")
nnoremap <silent> <Plug>NERDCommenterToEOL :call NERDComment("n", "ToEOL")
xnoremap <silent> <Plug>NERDCommenterNested :call NERDComment("x", "Nested")
nnoremap <silent> <Plug>NERDCommenterNested :call NERDComment("n", "Nested")
xnoremap <silent> <Plug>NERDCommenterMinimal :call NERDComment("x", "Minimal")
nnoremap <silent> <Plug>NERDCommenterMinimal :call NERDComment("n", "Minimal")
xnoremap <silent> <Plug>NERDCommenterToggle :call NERDComment("x", "Toggle")
nnoremap <silent> <Plug>NERDCommenterToggle :call NERDComment("n", "Toggle")
xnoremap <silent> <Plug>NERDCommenterComment :call NERDComment("x", "Comment")
nnoremap <silent> <Plug>NERDCommenterComment :call NERDComment("n", "Comment")
nnoremap <silent> <Plug>MarkSearchPrev :if !mark#SearchNext(1)|execute 'normal! #zv'|endif
nnoremap <silent> <Plug>MarkSearchNext :if !mark#SearchNext(0)|execute 'normal! *zv'|endif
nnoremap <silent> <Plug>MarkSearchAnyPrev :call mark#SearchAnyMark(1)
nnoremap <silent> <Plug>MarkSearchAnyNext :call mark#SearchAnyMark(0)
nnoremap <silent> <Plug>MarkSearchCurrentPrev :call mark#SearchCurrentMark(1)
nnoremap <silent> <Plug>MarkSearchCurrentNext :call mark#SearchCurrentMark(0)
nnoremap <silent> <Plug>MarkToggle :call mark#Toggle()
nnoremap <silent> <Plug>MarkAllClear :call mark#ClearAll()
nnoremap <silent> <Plug>MarkClear :call mark#DoMark(mark#CurrentMark()[0])
vnoremap <silent> <Plug>MarkRegex :call mark#MarkRegex(mark#GetVisualSelectionAsRegexp())
nnoremap <silent> <Plug>MarkRegex :call mark#MarkRegex('')
vnoremap <silent> <Plug>MarkSet :call mark#DoMark(mark#GetVisualSelectionAsLiteralPattern())
nnoremap <silent> <Plug>MarkSet :call mark#MarkCurrentWord()
nmap <F4> :SrcExplToggle                "打开/闭浏览窗口
nmap <F2> :NERDTreeToggle
nnoremap <silent> <F3> :Grep
nmap <F12> :!find . -iname '*.c' -o -iname '*.cpp' -o -iname '*.h' -o -iname '*.hpp' > cscope.files :!cscope -b -i cscope.files -f cscope.out :cs reset
inoremap <expr> 	 pumvisible() ? "\" : "\	"
inoremap  u
imap ,ihn :IHN
imap ,is :IHS:A
imap ,ih :IHS
let &cpo=s:cpo_save
unlet s:cpo_save
set autochdir
set autoindent
set background=dark
set backspace=indent,eol,start
set cindent
set completefunc=youcompleteme#Complete
set completeopt=menuone
set cpoptions=aAceFsB
set cscopequickfix=s-,c-,d-,i-,t-,e-
set cscopetag
set cscopeverbose
set fileencodings=utf-8,gbk,utf-16,big5
set helplang=cn
set hlsearch
set incsearch
set langmenu=zh_CN.UTF-8
set laststatus=2
set mouse=a
set omnifunc=youcompleteme#OmniComplete
set ruler
set runtimepath=~/.vim,~/.vim/bundle/vundle,~/.vim/bundle/ListToggle,~/.vim/bundle/a.vim,~/.vim/bundle/c.vim,~/.vim/bundle/cpp.vim,~/.vim/bundle/grep.vim,~/.vim/bundle/auto-pairs,~/.vim/bundle/cSyntaxAfter,~/.vim/bundle/indentLine,~/.vim/bundle/Mark--Karkat,~/.vim/bundle/nerdcommenter,~/.vim/bundle/nerdtree,~/.vim/bundle/vim-powerline,~/.vim/bundle/repeat.vim,~/.vim/bundle/SrcExpl,~/.vim/bundle/std_c.zip,~/.vim/bundle/tagbar,~/.vim/bundle/YouCompleteMe,~/.vim/bundle/ShowMarks,/opt/share/vim/vimfiles,/opt/share/vim/vim74,/opt/share/vim/vimfiles/after,~/.vim/after,~/.vim/bundle/vundle/,~/.vim/bundle/vundle/after,~/.vim/bundle/ListToggle/after,~/.vim/bundle/a.vim/after,~/.vim/bundle/c.vim/after,~/.vim/bundle/cpp.vim/after,~/.vim/bundle/grep.vim/after,~/.vim/bundle/auto-pairs/after,~/.vim/bundle/cSyntaxAfter/after,~/.vim/bundle/indentLine/after,~/.vim/bundle/Mark--Karkat/after,~/.vim/bundle/nerdcommenter/after,~/.vim/bundle/nerdtree/after,~/.vim/bundle/vim-powerline/after,~/.vim/bundle/repeat.vim/after,~/.vim/bundle/SrcExpl/after,~/.vim/bundle/std_c.zip/after,~/.vim/bundle/tagbar/after,~/.vim/bundle/YouCompleteMe/after,~/.vim/bundle/ShowMarks/after
set shiftwidth=4
set showmatch
set softtabstop=4
set statusline=%F%m%r%h%w\ [FORMAT=%{&ff}]\ [TYPE=%Y]\ [POS=%l,%v][%p%%]\ %{strftime(\"%d/%m/%y\ -\ %H:%M\")}
set noswapfile
set tabstop=4
set termencoding=utf-8
set updatetime=2000
" vim: set ft=vim :
