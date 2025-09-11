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

disp('## Rectangular Skewed Frustum');

disp('## Volume');

syms lx1 ly1 lx2 ly2 lz
syms vol

disp('## Center of Mass');

syms cg_x cg_y cg_z

disp('## Moments of Inertia');

syms x0 y0 z0 % 0th base center coordinates
syms x1 y1 z1 % 1st base center coordinates
syms Ixx Iyy Izz Ixy Ixz Iyz
