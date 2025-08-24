v1 = [ 1.0, 0.0, 0.0 ];
v2 = [ 0.0, 1.0, 0.0 ];
v3 = [ 0.0, 0.0, 1.0 ];
v4 = [ 1.0, 2.0, 3.0 ];

v4_v1 = cross( v4, v1 )
v4_v2 = cross( v4, v2 )
v4_v3 = cross( v4, v3 )
v2_v4 = cross( v2, v4 )
v3_v4 = cross( v3, v4 )

r = [ 1.0, 2.0, 3.0 ];
f = [ 4.0, 5.0, 6.0 ];
t1 = cross( r, f )
t2 = cross( f, r )
