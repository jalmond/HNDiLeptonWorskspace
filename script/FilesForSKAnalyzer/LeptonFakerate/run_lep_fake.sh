#!/bin/bash

root -l -q -b 'make_fakreta_mu.C(0)'
root -l -q -b 'make_fakreta_mu.C(1)'
root -l -q -b 'make_fakreta_mu.C(2)'
root -l -q -b 'make_fakreta_mu.C(3)'

root -l -q -b 'make_fakreta_el.C(0)'
root -l -q -b 'make_fakreta_el.C(1)'
root -l -q -b 'make_fakreta_el.C(2)'
root -l -q -b 'make_fakreta_el.C(3)'
