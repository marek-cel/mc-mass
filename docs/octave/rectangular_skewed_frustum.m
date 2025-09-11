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

disp('## Rectangular skewed frustum');

disp('## Volume');

syms lx1 ly1 lx2 ly2 lz
syms vol
