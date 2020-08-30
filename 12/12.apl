split ← {⌊10⊤(⍵÷(10*⌽(⍳⌈10⍟1+⍵)-1))}
join ← {+/⍵×10*(⌽⍳⍴⍵)-1}
zeroPad ← { 4 ⍴ ⍵ ∪ 0 0 0 0 }
orderHL ← { ⍵[⍒⍵] }
orderLL ← { ⍵[⍋⍵] }

step ← { (join ¨ orderHL ¨ zeroPad ¨ split ¨ ⍵) - (join ¨ orderLL ¨ zeroPad ¨ split ¨ ⍵) }

n ← (999 + ⍳9000) ~ (1111×⍳9)

n6 ← step step step step step step n
n7  ← step n6
(+/ (n7 = 6174) - (n6 = 6174))
