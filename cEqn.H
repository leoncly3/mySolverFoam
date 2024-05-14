fvScalarMatrix cEqn
(
    dim_t*fvm::ddt(c)
    -M*dim_x2*fvc::laplacian(u)
);

cEqn.solve();
