fvScalarMatrix uEqn
(
    kappa*dim_x2*fvc::laplacian(c)
    -2*Q_s*((c - c_alpha)*(pow(c_beta - c, 2)) - (pow(c - c_alpha, 2))*(c_beta - c)) + fvm::Sp(1,u)
);

uEqn.solve();
