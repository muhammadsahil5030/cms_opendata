# cms_opendata
This repository contains the cms opendata analysis using docker container.
```
mkdir cms_opendata_work
chmod -R 777 cms_opendata_work
docker run -it --name my_opendata --net=host --env="DISPLAY" -v $HOME/.Xauthority:/home/cmsusr/.Xauthority:rw  -v ${HOME}/cms_opendata_work:/code cmsopendata/cmssw_7_6_7-slc6_amd64_gcc493 /bin/bash
```
```
docker start -i my_opendata
```
A demo for testing and validation
```
mkdir Demo
cd Demo
mkedanlzr DemoAnalyzer
scram b
```
make these changes to the confFile_cfg.py in the Demo/DemoAnalyzer/python directory:
1) Replace "file:myfile.root" with "root://eospublic.cern.ch//eos/opendata/cms/Run2015D/SingleElectron/MINIAOD/08Jun2016-v1/10000/001A703B-B52E-E611-BA13-0025905A60B6.root"
2) change -1 to 10 in process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1)).
   
Run the cms executable
```
cmsRun DemoAnalyzer/python/ConfFile_cfg.py
```
