pkg load geometry;

v1 = [ 1.0 2.0 3.0 ];
v2 = [ 2.0 3.0 4.0 ];

l1 = norm( v1 );
l2 = norm( v2 );

fprintf('l1= %f\n', l1);

v1_norm = normalizeVector(v1);
fprintf('v1_norm= %f %f %f\n', v1_norm(1),v1_norm(2),v1_norm(3));

v2_norm = normalizeVector(v2);
fprintf('v2_norm= %f %f %f\n', v2_norm(1),v2_norm(2),v2_norm(3));
