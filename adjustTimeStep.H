#include "fvCFD.H"

// 计算场变量残差的辅助函数,选择空间残差
scalar computeResidual(const volScalarField& field)
{
    volVectorField gradField = fvc::grad(field);
    volScalarField magGradField(mag(gradField));
    return gSum(magGradField);//计算标量场的梯度，得到一个向量场，计算向量场的模长之和，最后返回的是一个标量值
}

// 调整时间步长的辅助函数
void adjustTimeStep(Time& runTime, scalar previousResidualc, scalar currentResidualc, scalar previousResidualu, scalar currentResidualu, scalar relaxationFactor)
{
    // 计算当前残差和上一个时间步长残差之比
    scalar residualRatioc = currentResidualc / previousResidualc;
    scalar residualRatiou = currentResidualu / previousResidualu;

    // 选择较大的残差比率，二选一就行，这样就包含了c和u
    scalar maxResidualRatio = max(residualRatioc, residualRatiou);

     scalar deltaT = runTime.deltaT().value(); // 获取当前时间步长

    if (maxResidualRatio > 1.0)
    {
        // 如果残差增加，减少时间步长
        runTime.deltaT() *= relaxationFactor / maxResidualRatio;
    }
    else
    {
        // 如果残差减少或相等，增加时间步长
        runTime.deltaT() /= relaxationFactor * maxResidualRatio;
    }

    // 增加一个最小变化量的阈值
    /*const scalar minChange = 1e-4;
    if (fabs(maxResidualRatio - 1.0) < minChange)
    {
        deltaT *= (1.0 + minChange);
    }*/

    runTime.setDeltaT(deltaT);  // 设置新的时间步长


    Info << "New deltaT: " << runTime.deltaT() << nl << endl;
    Info << "Previous deltaT: " << runTime.deltaT() << nl <<endl;
    Info << "Previous Residual c: " << previousResidualc << ", Current Residual c: " << currentResidualc << nl;
    Info << "Previous Residual u: " << previousResidualu << ", Current Residual u: " << currentResidualu << nl;

}




