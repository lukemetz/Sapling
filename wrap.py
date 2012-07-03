from wrapComponent import wrapComponent
from wrapManager import wrapManager
import os
import json
pwd = os.path.dirname(__file__)

if pwd == "":
  pwd = "."

f = open(pwd+"/components.json")
components = json.loads(f.read())
allHeaders = [];
allComponents = [];

for com in components:
  dictionary = components[com];
  dictionary["name"] = com;
  wrapComponent(dictionary);
  if dictionary["header"] not in allHeaders:
    allHeaders.append(dictionary["header"]);
  allComponents.append(com);

wrapManager(allComponents, allHeaders);

"""component = {"name": "TransformComponent",\
    "params":{"pos" : "vec3", "scale" : "vec3", "rot" : "vec3"},\
    "header" : 'components.h'}
wrapComponent(component);

component = {"name": "CameraComponent", \
    "params":{}, "header": 'components.h'}
wrapComponent(component)


component = {"name": "InputComponent", \
    "params":{}, "header": 'components.h'}
wrapComponent(component)


components = ["TransformComponent", "CameraComponent", "InputComponent"]
includes = ["components.h", "userComponents.h"]
wrapManager(components, includes)"""
