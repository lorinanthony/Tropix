#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <tuple>

#define DEBUG false


int main(int nbargs, char** args) {

  if (nbargs != 4) {
    std::cout << "Syntax: " << args[0] << " barcode_file mlp_file outfile_prefix" << std::endl;
    return 0;
  }

  std::ifstream in (args[1]);
  std::ifstream in2 (args[2]);

  // Read in the barcode
  int dimmax = -1;
  std::set<std::tuple<int, double, double> > barcode;
  {
    double b,d;
    int dim=-1;
    while ((in >> b >> d >> dim)) {
      std::tuple<int, double, double> t(dim,b,d);
      barcode.insert(t);
      dimmax = std::max(dim, dimmax);
    }
  }
  // sanity check
  if (DEBUG) 
    for (auto & t : barcode) 
      std::cout << std::get<0>(t) << " " << std::get<1>(t) << " "  << std::get<2>(t) << std::endl;
  

  // Read in m, l and p arrays
  std::vector<std::tuple<double, int, int> > mlp;
  {
    double m;
    int l, p;
    while ((in2 >> m >> l >> p)) {
      std::tuple<double, int, int> t(m, l, p);
      mlp.push_back(t);
    }
  }
  // sanity check
  if (DEBUG)
    for (auto & t : mlp) 
      std::cout << std::get<0>(t) << " " << std::get<1>(t) << " "  << std::get<2>(t) << std::endl;

  
  // computing polynomials
  std::set<std::tuple<int, double, double> >::iterator sit = barcode.begin();
  std::vector<std::pair<double, double> > X (barcode.size());
  for (int dimref=0; dimref<=dimmax; dimref++) {

    // First, adapt the barcode data 
    X.clear();
    double m=0;
    int  l=0, p=0, n=0;
    while ( sit != barcode.end() && std::get<0>(*sit) == dimref) {
      int dim = std::get<0>(*sit);
      double b = std::get<1>(*sit);
      double d = std::get<2>(*sit);      
      m = std::get<0>(mlp[dim]);
      l = std::get<1>(mlp[dim]);
      p = std::get<2>(mlp[dim]);
      X.push_back(std::pair<double, double> (std::min(m*(d-b), b), d-b)); 
      sit++;
      n++;
    }
    while (n++ < l+p)
      X.push_back(std::pair<double, double> (0,0));

    // sanity check
    if (DEBUG)
      std::cout << X.size() << std::endl;

    // Then, initialize the lookup table
    int size = (l+1)*(p+1);
    double* Q = new double[2*size];
    for (int i=0; i<2*size; i++)
      Q[i] = 0;

    // Then, fill in the table by dynamic programming
    int r = 1;
    int ind = 0;
    n=0;
    for (std::vector<std::pair<double, double> >::iterator vit = X.begin();
	 vit != X.end(); vit++,n++) {
      std::pair<double, double> bar = *vit;
      double b0 = std::get<0>(bar);
      double b1 = std::get<1>(bar);
      r = 1-r;
      ind = r*size-1;
      int shift = (r==0)? size : (-size);
      for (int lt=0; lt<=l; lt++)
	for (int pt=0; pt<=p; pt++) {
	  ind++;
	  if (lt == 0 && pt == 0)
	    Q[ind] = 0;
	  else if (lt == 0) {
	    if (pt > n+1)
	      Q[ind] = Q[ind-1]; //Q[r][lt][pt-1];
	    else {
	      // double a = Q[1-r][lt][pt], b = Q[1-r][lt][pt-1] + b0 + b1;
	      double a = Q[ind+shift], b = Q[ind+shift-1] + b0 + b1;
	      if (a<b) a = b;
	      Q[ind] = a;
	    }
	  }
	  else if (pt == 0) {
	    if (lt > n+1)
	      Q[ind] = Q[ind-p-1]; //Q[r][lt -1][pt];
	    else {
	      // double a = Q[1-r][lt][pt], b = Q[1-r][lt-1][pt] + b1; 
	      double a = Q[ind+shift], b = Q[ind+shift-p-1] + b1; 
	      if (a<b) a = b;
	      Q[ind] = a;
	    }
	  }
	  else {
	    // double a = Q[1-r][lt][pt], b = Q[1-r][lt-1][pt] + b1, c = Q[1-r][lt][pt-1] + b0 + b1;  
	    double a = Q[ind+shift], b = Q[ind+shift-p-1] + b1, c = Q[ind+shift-1] + b0 + b1;  
	    if (a<b) a = b;
	    if (a<c) a = c;
	    Q[ind] = a;
	  }
	}
    }

    // Finally, output the resulting grid, as stored in Q[r]

    std::string outname (args[3]);
    outname += std::to_string(dimref);
    std::ofstream out (outname.c_str());
    int pt = 0;
    for (ind = r*size; ind < r*size + size; ind++,pt++) {
      out << Q[ind];
      if (pt < p) out << " ";
      else {out << std::endl; pt = -1;}
    }      

    delete[] Q;
  }


    

  return 0;

}



