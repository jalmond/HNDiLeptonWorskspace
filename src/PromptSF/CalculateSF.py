import os 

def GetOther(nData,nZZ,nWZ, nZG):
    
    return (nData-nZZ-nWZ-nZG)


ZZ_CR_D=204 + 67
ZZ_CR_ZZ = 174.97+31.42 + 53.91 + 10.31
ZZ_CR_WZ = 0
ZZ_CR_ZG = 0
ZZ_CR_Other = GetOther(ZZ_CR_D,
                            ZZ_CR_ZZ,
                            ZZ_CR_WZ,
                            ZZ_CR_ZG)

WZ_CR_D = 1158.0 + 492.0 + 1311.0
WZ_CR_ZZ = 43.36 + 1.59 + 10.76 + 0.94 + 37.9 + 2.38
WZ_CR_WZ = 983.05 + 395.53 + 1149.42
WZ_CR_ZG = 1.57 + 5.7 +9.38+4.68
WZ_CR_Other = GetOther(WZ_CR_D,
                            WZ_CR_ZZ,
                            WZ_CR_WZ,
                            WZ_CR_ZG)

ZG_CR_D = 228.0+237.0+530.0
ZG_CR_ZZ = 76.48+1.36+32.55+0.94+86.87+1.79
ZG_CR_WZ = 15.83+4.85+21.2
ZG_CR_ZG = 91.82+164.91+361.19
ZG_CR_Other = GetOther(ZG_CR_D,
                            ZG_CR_ZZ,
                            ZG_CR_WZ,
                            ZG_CR_ZG)


a = WZ_CR_D - WZ_CR_Other
b = ZZ_CR_D - ZZ_CR_Other
c = ZG_CR_D - ZG_CR_Other

import numpy 
#B = numpy.array([ SFWZ, SFZZ,SFZG]) 
A = numpy.array([[WZ_CR_WZ, WZ_CR_ZZ,WZ_CR_ZG], 
                 [ZZ_CR_WZ, ZZ_CR_ZZ,ZZ_CR_ZG], 
                 [ZG_CR_WZ, ZG_CR_ZZ,ZG_CR_ZG]])

inverse_array = numpy.linalg.inv(A) 

C = numpy.array([ a, b,c])


print (numpy.multiply(inverse_array,y))
