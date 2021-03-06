/*    Copyright (C) 2013  kklloh

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef __FLUID_SIMULATOR_H__
#define __FLUID_SIMULATOR_H__

#include "StaggeredGrid.hh"
#include "VTKWriter.hh"
#include "SORSolver.hh"
#include "FileReader.hh"

class FluidSimulator
{
  public:
  			FluidSimulator();
      FluidSimulator( const FileReader & conf );

      /// Simulates a given time-length
      void simulate             ( real duration              );
      void simulateTimeStepCount( unsigned int nrOfTimeSteps );


      // Getter functions for the internally stored StaggeredGrid
            StaggeredGrid & grid();
      const StaggeredGrid & grid() const;
			void computeFG();
			void composeRHS2D();
			void setUVBC2D();
			void initFields();
			void adapUV2D();

  private:
/*			void setNBC2D(Array& bcVecU,Array& bcVecV, int NX, int NY, int nGhost, int type);
			void setEBC2D(Array& bcVecU,Array& bcVecV, int NX, int NY, int nGhost, int type);
			void setSBC2D(Array& bcVecU,Array& bcVecV, int NX, int NY, int nGhost, int type);
			void setWBC2D(Array& bcVecU,Array& bcVecV, int NX, int NY, int nGhost, int type); */
			void setNBC2D(real Uw,real Vw, int NX, int NY, int nGhost, int type);
			void setEBC2D(real Uw,real Vw, int NX, int NY, int nGhost, int type);
			void setSBC2D(real Uw,real Vw, int NX, int NY, int nGhost, int type);
			void setWBC2D(real Uw,real Vw, int NX, int NY, int nGhost, int type);			
			void setDelta_t2D();
			void normalizePressure();
  			StaggeredGrid grid_;
			SORSolver psolver_;
			Array du2dx, duvdy, d2udx2, d2udy2, dpdx, duvdx, dv2dy, d2vdx2, d2vdy2, dpdy; //Kept in array form since post processing will be easier? can change to real if insufficient memory
			int Ntimes_,pnorm_,rescheckfreq_,writeVTKfreq_;
			real gam_;
			real dt_, tau_ = 0.9, t_end;
			real RE_;
			real gx_;
			real gy_;
			real uinit_, vinit_, pinit_;
            real U_NBC_, V_NBC_, U_EBC_, V_EBC_, U_SBC_, V_SBC_, U_WBC_, V_WBC_ = 0.;
            int Nbctype_, Ebctype_, Sbctype_, Wbctype_ = 0;
};



#endif
