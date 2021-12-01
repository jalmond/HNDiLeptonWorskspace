#!/bin/bash

root -l -q -b 'make_promptrate_mu.C(0)'
root -l -q -b 'make_promptrate_mu.C(1)'
root -l -q -b 'make_promptrate_mu.C(2)'
root -l -q -b 'make_promptrate_mu.C(3)'

root -l -q -b 'make_promptrate_el.C(0)'
root -l -q -b 'make_promptrate_el.C(1)'
root -l -q -b 'make_promptrate_el.C(2)'
root -l -q -b 'make_promptrate_el.C(3)'
