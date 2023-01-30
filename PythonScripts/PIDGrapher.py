import sys
from bokeh.plotting import figure, output_file,show
import numpy
import itertools
from bokeh.palettes import Dark2_5 as palette

def main():
    if(len(sys.argv) !=2):
        return
    
    output_file(sys.argv[1][:len(sys.argv[1])-5]+".html")
    csv = open(sys.argv[1],"r")
    Names = []
    Names = csv.readline().split(",")
    Data = [[] for i in range(len(Names))]
    s = csv.readline()
    while( s!=""):
        s = s.strip().split(",")
        for i in range(len(s)):
            Data[i].append(s[i])
        s = csv.readline()
    print("\n",Data)
    graph = figure(title = sys.argv[1])
    colors = itertools.cycle(palette)    
    for i,color in zip(range(len( Data)),colors):
        graph.line(range(len(Data[i])),Data[i],legend_label=Names[i],color=color)
    show(graph)



        


if __name__ == "__main__":
    main()