import matplotlib.pyplot as plot


def getProvinceGraph(xdata, ydata, title, source, var):

    for i in range(len(xdata)):
        xdata[i] = xdata[i][0:3].upper()

    plot.title(title)
    plot.xlabel("Provinces")
    plot.ylim(ymin = -1, ymax = max(ydata) + 1)
    plot.ylabel(f"{var} Values")
    plot.scatter(xdata, ydata, label = f"{var} From {source}")
    plot.legend(loc="upper left")
    plot.grid()
    plot.savefig(f'{title}.png')


    return 0