/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2024 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    mySolver

Description

\*---------------------------------------------------------------------------*/
#include "fvCFD.H"
#include "pimpleControl.H"
#include "adjustTimeStep.H"

int main(int argc, char *argv[])
{
    #include "setRootCase.H"
    #include "createTime.H"
    #include "createMesh.H"

    pimpleControl pimple(mesh);  // 初始化 PIMPLE 控制对象

    #include "createFields.H"
/* scalar previousResidualc = 1.0;
    scalar previousResidualu = 1.0;
    scalar relaxationFactor = 0.5;
*/
    Info << "\nCalculating temperature distribution\n" << endl;

    while (pimple.loop(runTime))  // 时间步循环
    {
        Info << "Time = " << runTime.timeName() << nl << endl;

        // 外部迭代循环
        while (pimple.loop())
        {
            
            #include "cEqn.H"  // 求解浓度方程
            // 内部校正循环
            while (pimple.correct())
            {
            #include "uEqn.H"  // 求解温度方程
            }
        }

        runTime.write();  // 写入当前时间步的结果

        // 计算当前残差
 /*      scalar currentResidualc = computeResidual(c);
        scalar currentResidualu = computeResidual(u);

        Info << "Residual for c: " << currentResidualc << ", Residual for u: " << currentResidualu << endl;

       // 调整时间步长 
        adjustTimeStep(runTime, previousResidualc, currentResidualc, previousResidualu, currentResidualu, relaxationFactor);

        // 更新上一个时间步的残差
        previousResidualc = currentResidualc;
        previousResidualu = currentResidualu;
*/
        Info << "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;
    }

    Info << "End\n" << endl;

    return 0;
}



// ************************************************************************* //
