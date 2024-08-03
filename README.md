# cms_opendata
This repository contains the cms opendata analysis using docker container.
```
mkdir cms_opendata_work
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
Run the cms executable
```

```
