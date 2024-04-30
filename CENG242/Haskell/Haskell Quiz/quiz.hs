nmap f [] = []
nmap f ( x : xs ) = ( f x ):(nmap f xs )

nfilter f [] = []
nfilter f ( x : xs ) = if ( f x ) then ( x :( nfilter f xs ))
                        else ( nfilter f xs )

reduce f s [] = s
reduce f s ( x : xs ) = f x ( reduce f s xs )

for m n f s = if (m>n) then s
                else for (m+1) n f ( f m s )
comp f g x y = f x (g x y )

iter 0 f s = s
iter n f s = iter (n -1) f ( f s )

zpt a [] = [a]
zpt a ( x : xs ) = if a > x then a :( x : xs )
                    else x :( zpt a xs )