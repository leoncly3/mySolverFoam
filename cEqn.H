fvScalarMatrix cEqn
(
    dim_t*fvm::ddt(c)
    -dim_x2*fvm::laplacian(M,u)
);

cEqn.solve();
