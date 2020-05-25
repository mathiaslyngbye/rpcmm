#!/bin/bash

for node in $(docker node ls --format "{{.Hostname}}");
do
echo  \[$node\];
docker node ps $node --format "=> {{.Name}} ({{.DesiredState}})";
done;
