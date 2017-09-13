# Tropical Sufficient Statistics for Persistent Homology (Tropix)
In this repository, we present code that uses an embedding in Euclidean space based on tropical geometry to generate stable sufficient statistics for barcodes --- multiscale summaries of topological characteristics that capture the “shape” of data, but have complex structures and are therefore difficult to use in statistical settings. We refer to this software as Tropix. This statistical sufficiency result was derived in [Monod et al. (2017)](https://arxiv.org/abs/1709.02647) and allows for the assumption of classical probability distributions on Euclidean representations of barcodes. This in turn makes a variety of parametric inference methods amenable to barcodes, all while maintaining their initial interpretations. In particular, this work shows that exponential family distributions may be assumed, and that likelihoods for persistent homology may be constructed. In this repository, we use Tropix to conceptually demonstrate sufficiency and illustrate its utility in persistent homology dimensions 0 and 1 with concrete parametric applications to HIV and avian influenza data.

Tropix is implemented in three different language environments: (1) Matlab, (2) Python, and (3) C++. The preprocessed data used in Monod et al. (2017) were obtained from publicly available sources and preprocessed.

### The MATLAB Environment
MATLAB is a multi-paradigm numerical computing environment and a proprietary programming language developed by [MathWorks](https://www.mathworks.com/index-c.html). MATLAB allows matrix manipulations, plotting of functions and data, implementation of algorithms, creation of user interfaces, and interfacing with programs written in other languages. For more on licensing options, please visit [here](https://www.mathworks.com/campaigns/products/ppc/google/matlab-toolbox-price-request.html?form_seq=reg).

### C++ Functions Required for Tropix
The code in this repository assumes that basic C++ functions and applications are already set up on the running personal computer or cluster. If not, certain versions of Tropix functions may not work properly. A simple option is to use [gcc] (https://gcc.gnu.org/). macOS users may use this collection by installing the [Homebrew package manager](http://brew.sh/index.html) and then typing the following into the terminal:

    brew install gcc

For macOS users, the Xcode Command Line Tools include a GCC compiler. Instructions on how to install Xcode may be found [here](http://railsapps.github.io/xcode-command-line-tools.html). For extra tips on how to run C++ on macOS, please visit [here](http://seananderson.ca/2013/11/18/rcpp-mavericks.html). For tips on how to avoid errors dealing with "-lgfortran" or "-lquadmath", please visit [here](http://thecoatlessprofessor.com/programming/rcpp-rcpparmadillo-and-os-x-mavericks-lgfortran-and-lquadmath-error/).

### Data Sources and Preprocessing
The respective virus datasets in Monod et al. (2017) were obtained from public sources. We give the details on their sources and preliminary data processing procedures below.

#### **HIV Dataset**
HIV polymerase sequences derived from patients included in the MSM HIV transmission cluster ([Patiño-Galindo et al., 2017](http://journals.plos.org/plosone/article?id=10.1371/journal.pone.0171062)) were retrieved from supplementary material made public on GenBank. Sequences derived from unrelated patients were obtained from the Los Alamos HIV database in October 2016. Only sequences from the same subtype (HIV subtype B), and spanning the polymerase region were considered. In order to ensure that these sequences were not epidemiologically related, redundant sequences were removed after a clustering analysis with a specified genetic distance threshold of 5%, using CD-HIT ([Huang et al., 2010](https://academic.oup.com/bioinformatics/article/26/5/680/212234/CD-HIT-Suite-a-web-server-for-clustering-and)). All sequences were aligned using MAFFTv7 ([Katoh and Standley, 2013](https://academic.oup.com/mbe/article-lookup/doi/10.1093/molbev/mst010)).

#### **Avian Influenza**
Hemagglutinin (HA) and Neuraminidase (NA) genes of avian influenza A were downloaded in August 2017 from the Influenza Virus Database of the National Center for Biotechnology Information (NCBI). The resulting gene datasets were aligned with MAFFTv7 ([Katoh and Standley, 2013](https://academic.oup.com/mbe/article-lookup/doi/10.1093/molbev/mst010)). Concatenated sequences of both genes (derived from the same sample) were generated with the package ape written in R ([Paradis et al., 2004](https://academic.oup.com/bioinformatics/article/20/2/289/204981/APE-Analyses-of-Phylogenetics-and-Evolution-in-R)). The multiple sequence alignments was trimmed with TrimAl ([Capella-Gutierrez et al., 2009](https://academic.oup.com/bioinformatics/article-lookup/doi/10.1093/bioinformatics/btp348)) in order to remove regions of sparse homology (i.e. biologically shared ancestry).

In both viral examples, pairwise distances were obtained using PAUP ([Swofford, 2001](http://onlinelibrary.wiley.com/doi/10.1002/0471650129.dob0522/abstract)) and were calculated by using the GTR + GAMMA (4 CAT) model, which is commonly used for studying HIV and Influenza datasets ([Tian et al., 2015](http://www.pnas.org/content/112/1/172.abstract); [Worobey et al., 2016](https://www.nature.com/nature/journal/v539/n7627/full/nature19827.html)). The GTR model is a time reversible model that considers variable base frequencies, where each pair of nucleotide substitutions occur at different rates ([Donnelly and Tavaré, 1995](http://www.annualreviews.org/doi/abs/10.1146/annurev.ge.29.120195.002153)). Combined with a gamma distribution, it also accounts for rate variation among sites ([Yang, 1995](http://www.genetics.org/content/139/2/993)). The use of a substitution model when calculating genetic distances, as carried out according to these procedures, leads to estimates that are considered more biologically accurate.

### Relevant Citations
A. Monod, S. Kališnik Verovšek, J.Á. Patiño-Galindo, and L. Crawford (2017). Tropical sufficient statistics for persistent homology with a parametric application to infectious viral disease. arXiv. 1709.02647.

### Questions and Feedback
For questions or concerns with the Tropix functions, please contact
[Anthea Monod](mailto:rr2579@cumc.columbia.edu), [Melissa McGuirl](mailto:melissa_mcguirl@brown.edu), or [Lorin Crawford](mailto:lorin_crawford@brown.edu).

We appreciate any feedback you may have with our repository and instructions.
