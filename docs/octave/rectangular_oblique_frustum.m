clear all

pkg load symbolic

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% function to diaply equations in latex format
function disp_latex(name, eq)
    disp('$$');
    disp(['', name, ' = ', latex(eq)]);
    disp('$$');
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

disp('## Rectangular Oblique Frustum');

disp('## Volume');

syms lx1 ly1 lx2 ly2 lz
syms z
syms vol

vol = lz*simplify(int((ly1 + (ly2 - ly1)*(z/lz))*(lx1 + (lx2 - lx1)*(z/lz))/lz, z, 0, lz));
disp_latex('V', vol);

disp('## Center of Mass');

syms x1 y1 z1 % lower surface (base) center coordinates
syms x2 y2 z2 % upper surface (base) center coordinates
syms cg_x cg_y cg_z

% TODO

disp('## Moments of Inertia About Center of Mass');

syms Ixx Iyy Izz Ixy Ixz Iyz
