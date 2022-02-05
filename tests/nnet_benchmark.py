# -*- coding: utf-8 -*-
"""
Created on Thu Feb  3 12:17:50 2022

@author: azebc
"""

import numpy as np
import time
import psutil

# Limit to single thread only
psutil.cpu_count()
p = psutil.Process()
p.cpu_affinity()
p.cpu_affinity([0])

def relu(z):
    z[z < 0] = 0
    return z
    
def sigmoid(z):
    return (1 / (1 + np.exp(-z)))

def get_activation(z, method):
    if method == 'relu':
        return relu(z)
    elif method == 'sigmoid':
        return sigmoid(z)

def parseStringToParams(line):
    line = line.strip('\n')[1:-1]
    line = line.split(', ')

    row_list = list()
    col_list = list()
    for elem in line:
        if elem[0] == '[' and elem[-1] == ']':
            val = float(elem[1:-1])
            col_list.append(val)
            row_list.append(col_list)
            col_list = list()
            
        elif elem[0] == '[':
            val = float(elem[1:])
            col_list.append(val)
            
        elif elem[-1] == ']':
            val = float(elem[:-1])
            col_list.append(val)
            row_list.append(col_list)
            col_list = list()
            
        else:
            val = float(elem)
            col_list.append(val)

    return np.array(row_list)


def getNetwork(weight_fname, act_fname):
    params = list()
    with open(weight_fname) as f:
        a = f.readlines(1)
        while a != []:
            params.append(parseStringToParams(a[0]))
            a = f.readlines(1)

    with open(act_fname) as f:
        a = f.readlines()
        
    acts = [elem.strip('\n') for elem in a]
    network = dict()
    network['params'] = params
    network['acts'] = acts
    
    return network

def getNumOfTrainableParams(network):
    num = 0
    for layer in network['params']:
        num += len(layer.reshape(-1, ))
    return num

def getNetworkPredict(network, x):
    params = network['params']
    acts = network['acts']
    
    w_list = params[::2]
    b_list = params[1::2]
    
    layer_count = len(w_list)
    
    for layer in range(layer_count):
        w = w_list[layer].T
        b = b_list[layer].T
        
        z = np.matmul(w, x) + b
        a = get_activation(z, acts[layer])
        x = a
    
    return a

import argparse


parser = argparse.ArgumentParser()
parser.add_argument('-e', '--epoch')
args = parser.parse_args()

EPOCH = 100000
if args.epoch is not None:
    EPOCH = int(args.epoch)

gate = 'mix'
weight_fname = 'weights_{}.txt'.format(gate)
act_fname = 'acts_{}.txt'.format(gate)
network = getNetwork(weight_fname, act_fname)

print("Network\n==============================");
print("Total trainable params: {}".format(getNumOfTrainableParams(network)))

x = np.array([[5], [1], [0]])
time_s = time.time()
for i in range(EPOCH):
    
    if i % (EPOCH // 10) == 0:
        print("Epoch-{}: {:.3f}s".format(i, time.time()-time_s))
    y_hat = getNetworkPredict(network, x)

print("Finished {} epochs in {:.3f}s".format(EPOCH, time.time()-time_s))
print("  > Each inference takes {:.3f}us".format((time.time()-time_s)/EPOCH*1e6))
