function f9950 pi1 pi2 pi3
def
var vi1
var vi2
var vi3
enddef

vi1 = pi2 * pi2

vi2 = ci4 * pi1
vi2 = vi2 * pi3

vi1 = vi1 - vi2


vi3 = call f9951 vi1
if vi3
vi2 = call f9949
endif


vi3 = call f9952 vi1
if vi3
vi2 = call f9948
endif


vi3 = call f9953 vi1
if vi3
vi2 = call f9947
endif


return vi1
end

function f9961 pi1 pi2 pi3
def
var vi1
var vi2
var vi3
enddef

vi1 = ci-1 * pi3

vi2 = ci2 * pi2

vi3 = vi1 - pi1
vi3 = vi3 / vi2

return vi3
end

function f9962 pi1 pi2 pi3
def
var vi1
var vi2
var vi3
enddef

vi1 = ci-1 * pi3

vi2 = ci2 * pi2

vi3 = vi1 + pi1
vi3 = vi3 / vi2

return vi3
end