Info<< "Reading myProperties\n" << endl;
IOdictionary myProperties
(
    IOobject
    (
        "myProperties",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ_IF_MODIFIED,
        IOobject::NO_WRITE
    )
);

dimensionedScalar c_alpha
(
    myProperties.lookup("c_alpha")
);


dimensionedScalar c_beta
(
    myProperties.lookup("c_beta")
);

dimensionedScalar Q_s
(
    myProperties.lookup("Q_s")
);

dimensionedScalar M
(
    myProperties.lookup("M")
);

dimensionedScalar kappa
(
    myProperties.lookup("kappa")
);

dimensionedScalar dim_t
(
	myProperties.lookup("dim_t")
);

dimensionedScalar dim_x1
(
	myProperties.lookup("dim_x1")
);

dimensionedScalar dim_x2
(
	myProperties.lookup("dim_x2")
);

Info<< "Reading field u\n" << endl;//添加u场，u就是换元的内容
volScalarField u
(
    IOobject
    (
        "u",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Reading field c\n" << endl;
volScalarField c
(
    IOobject
    (
        "c",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info << ""Reading field U\n" << endl;//设置U场并且设置为c的梯度
volVectorField U
(
    IOobject
    (
        "U",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    fvc::grad(c)
);

#include "createPhi.H"


