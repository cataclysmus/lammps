/*
  fix_rhok.h
*/

#ifdef FIX_CLASS

FixStyle(rhok,FixRhok)

#else

#ifndef __FIX_RHOK__
#define __FIX_RHOK__

#include "fix.h"

namespace LAMMPS_NS {

class FixRhok : public Fix
{
public:
  // Constructor: all the parameters to this fix specified in
  // the LAMMPS input get passed in
  FixRhok( LAMMPS* inLMP, int inArgc, char** inArgv );
  virtual ~FixRhok();
  
  // Methods that this fix implements
  // --------------------------------

  // Tells LAMMPS where this fix should act
  int setmask();

  // Initializes the fix at the beginning of a run
  void init();

  // Initial application of the fix to a system (when doing MD / minimization)
  void setup( int inVFlag );
  void min_setup( int inVFlag );

  // Modify the forces calculated in the main force loop, either when
  // doing usual MD, RESPA MD or minimization
  void post_force( int inVFlag );
  void post_force_respa( int inVFlag, int inILevel, int inILoop );
  void min_post_force( int inVFlag );

  // Compute the change in the potential energy induced by this fix
  double compute_scalar();
	
	// Compute the ith component of the vector associated with this fix
  double compute_vector( int inI );
	
private:
  // RESPA boilerplate
  int mNLevelsRESPA;

  // Defining parameters for this umbrella
	double mK[3], mKappa, mRhoK0;
  
	// Number of particles affected by the fix
	int mNThis;
	double mSqrtNThis;
	
	// Real and imaginary parts of rho_k := sum_i exp( - i k . r_i )
	double mRhoKLocal[2], mRhoKGlobal[2];
};

}  // namespace LAMMPS_NS

#endif // __FIX_RHOK__
#endif // FIX_CLASS

