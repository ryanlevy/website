//Given an MPS or IQMPS called "psi",
//and some particular bond "b" (1 <= b < psi.N())
//across which we want to compute the von Neumann entanglement

//"Gauge" the MPS to site b
psi.position(b); 

//Here assuming an MPS of ITensors, but same code works
//for IQMPS by replacing ITensor -> IQTensor

//Compute two-site wavefunction for sites (b,b+1)
ITensor wf = psi.A(b)*psi.A(b+1);

//SVD this wavefunction to get the spectrum
//of density-matrix eigenvalues
auto U = psi.A(b);
ITensor S,V;
auto spectrum = svd(wf,U,S,V);

//Apply von Neumann formula
//spectrum.eigs() is a Vector containing
//the density matrix eigenvalues
//(squares of the singular values)
Real SvN = 0.;
for(auto p : spectrum.eigs())
    {
    if(p > 1E-12) SvN += -p*log(p);
    }
printfln("Across bond b=%d, SvN = %.10f",b,SvN);

