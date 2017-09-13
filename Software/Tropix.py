#!/bin/env python

"""
A function that evaluates barcodes from a collection of  files  with  symmetric tropical polynomials on a grid.

Inputs: Pointers to files to be evaluates

Outputs: labels for classification, evaluation of barcodes by symmetric tropical polynomials on a grid, and sizes
of grid for each dimension (grids are square)

MUST HAVE symTropEvalFast in directory/path to run this 

Original code by Melissa R. McGuirl, Brown University 

Last updated: 04/14/17

Run: evaluateBC.py path2inputs path2tropinfo Airplane/Ant/Human Train/Test

"""
import os
import sys
from numpy import *
import progressbar
import time 
import glob


def main():
    
    inFile = sys.argv[1]
    inFile = open(inFile, 'r')
    tropInfo  = sys.argv[2]
    shape = sys.argv[3]
    group = sys.argv[4]
    lines = inFile.readlines()
    counter = 0
    # Evaluate each barcode under symmetric tropical polynomials 
    for line in lines:
        input  = '../data/' + line[:-1] 
        outFile = '../TropData/' + group + '/' + shape + '/' +   str(counter) + '-'
        cmd = './symTropEvalFast ' + input + ' ' + tropInfo + ' ' +  outFile
        os.system(cmd)
        counter +=1

if __name__ == "__main__":
    if len(sys.argv) < 4:
        print 'usage: python evaluateBC.py path2inputs path2tropinfo Group Train/test'
    else:
        main()    
 


 
