fvScalarMatrix uEqn
(
    dim_x2*fvm::laplacian(kappa,c)
    -2*Q_s*((c - c_alpha)*(pow(c_beta - c, 2)) - (pow(c - c_alpha, 2))*(c_beta - c)) + u
);

uEqn.solve();