#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = /root/myDVR/IPNC20130122/dvsdk_2_10_01_18/codec_engine_2_24/examples;/root/myDVR/IPNC20130122/dvsdk_2_10_01_18/dm365_codecs_01_00_06/packages;/root/myDVR/IPNC20130122/dvsdk_2_10_01_18/codec_engine_2_24/packages;/root/myDVR/IPNC20130122/dvsdk_2_10_01_18/xdais_6_24/packages;/root/myDVR/IPNC20130122/dvsdk_2_10_01_18/framework_components_2_25_00_04/packages;/root/myDVR/IPNC20130122/dvsdk_2_10_01_18/edma3_lld_1_06_00_01/packages;/root/myDVR/IPNC20130122/dvsdk_2_10_01_18/linuxutils_2_24_03/packages
override XDCROOT = /root/myDVR/IPNC20130122/dvsdk_2_10_01_18/xdctools_3_15_01_59
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = /root/myDVR/IPNC20130122/dvsdk_2_10_01_18/codec_engine_2_24/examples;/root/myDVR/IPNC20130122/dvsdk_2_10_01_18/dm365_codecs_01_00_06/packages;/root/myDVR/IPNC20130122/dvsdk_2_10_01_18/codec_engine_2_24/packages;/root/myDVR/IPNC20130122/dvsdk_2_10_01_18/xdais_6_24/packages;/root/myDVR/IPNC20130122/dvsdk_2_10_01_18/framework_components_2_25_00_04/packages;/root/myDVR/IPNC20130122/dvsdk_2_10_01_18/edma3_lld_1_06_00_01/packages;/root/myDVR/IPNC20130122/dvsdk_2_10_01_18/linuxutils_2_24_03/packages;/root/myDVR/IPNC20130122/dvsdk_2_10_01_18/xdctools_3_15_01_59/packages;..
HOSTOS = Linux
endif
