# cms_opendata

#### Install the Docker container from the official page of Docker **https://docs.docker.com/engine/install**
#### Installing in Ubuntu 20.04
1) Set up Docker's apt repository.
```
sudo apt-get update
sudo apt-get install ca-certificates curl
sudo install -m 0755 -d /etc/apt/keyrings
sudo curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc
sudo chmod a+r /etc/apt/keyrings/docker.asc

# Add the repository to Apt sources:
echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/ubuntu \
  $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | \
  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
sudo apt-get update
```
2) Install the Docker packages.
```
sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
```
3) Verify that the Docker Engine installation is successful by running the hello-world image.
```
sudo docker run hello-world
```
#### Using Docker with the CMS Open data
```
mkdir cms_opendata_work
chmod -R 777 cms_opendata_work
```
###### Use the link **https://opendata.cern.ch/docs/cms-guide-docker** for the available CMSSW container images
```
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
## CMS NanoAOD Open Data
There is no need to use the CMS virtual machine or docker container to analyze the NanoAOD data but simply use C++ or Python script to analyze the ROOT file because the data is stored in ROOT TTree

#### Downloading the data on local machine
1) Install cern opendata-client using PyPI or Docker
   ```
   pip install --user cernopendata-client
   ```
2) The data files are available at **https://opendata.cern.ch**. We can listing the data files using record id (recid) or by digital object identifier (doi) number.
   ```
   cernopendata-client get-file-locations --doi 10.7483/OPENDATA.CMS.TTK7.008J
   cernopendata-client get-file-locations --recid 1
   ```
3) Downloading data files using doi
   ```
   cernopendata-client download-files --doi 10.7483/OPENDATA.CMS.TTK7.008J
   ```
4) To download specific number of data files use
   ```
   cernopendata-client download-files --recid 5500 --filter-name file1.root, file2.root, ...
   ```
