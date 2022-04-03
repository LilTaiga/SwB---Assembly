function f9999 pi1
def
var vi1
var vi2
enddef

vi2 = call f9998 pi1

if vi2
return ci1
endif

vi2 = pi1 - ci1

vi1 = call f9999 vi2
vi1 = vi1 * pi1

return vi1
end





function f9998 pi1
def
enddef

if pi1
return ci0
endif

return ci1
end