import cv2
import matplotlib.pyplot as plt
import numpy as np


class Pgm:
    format = ""
    comment = ""
    lx = 0
    ly = 0
    maxVal = 0
    mat = np.array([])
    def __init__(self):
        pass
    def __init__(self, format, comment, lx, ly, maxVal):
        self.format = format
        self.comment = comment
        self.lx = lx
        self.ly = ly
        self.maxVal = maxVal
        self.mat = np.zeros((self.ly, self.lx), dtype=np.uint8)
    def read(self, path):
        with open(path, 'r') as f:
            self.format = f.readline().rstrip()
            self.comment = f.readline().rstrip()
            self.lx, self.ly = map(int, f.readline().rstrip().split())
            self.maxVal = int(f.readline().rstrip())
            for i in range(self.ly):
                self.mat[i] =  [c for c in f.readline().strip().split(' ')]
            
    def write(self, path):
        with open(path, 'w') as f:
            f.write(self.format + '\n')
            f.write(self.comment + '\n')
            f.write(str(self.lx) + ' ' + str(self.ly) + '\n')
            f.write(str(self.maxVal) + '\n')
            for i in range(self.ly):
                for j in range(self.lx):
                    f.write(str(self.mat[i][j]) + ' ')
                f.write('\n')
    def show(self):
        plt.imshow(self.mat, cmap='gray')
        plt.show()

    def grayValue(self):
        return np.average(self.mat)
    
    def stdDeviation(self):
        return np.std(self.mat)
    
    def getHist(self):
        hist = []
        flat = self.mat.flatten()
        for i in range(0, 256):
            hist.append(np.count_nonzero(flat == i))
        return np.array(hist)

    def getCumHist(self,hist):
        cumHist = []
        cumHist.append(hist[0])
        for i in range(1, 256):
            cumHist.append(cumHist[i-1] + hist[i])
        return np.array(cumHist)