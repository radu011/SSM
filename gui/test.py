import pyqtgraph as pg
from PySide6 import QtWidgets
import sys

def create_plot():
    app = QtWidgets.QApplication(sys.argv)

    win = pg.GraphicsLayoutWidget(show=True, title="Segmented Line Plot Example")
    plot = win.addPlot(title="Plot")

    # Punctele tale
    points = [(0, 0), (1, 0.8)]

    for i in range(len(points) - 1):
        x0, y0 = points[i]
        x1, y1 = points[i + 1]

        # Calculează unde se intersectează segmentul cu y = 0.4
        if y0 < 0.4 <= y1:
            # Interpolarea liniară pentru a găsi punctul de intersecție
            intersect_x = x0 + (x1 - x0) * (0.4 - y0) / (y1 - y0)

            # Segmentul de jos
            plot.plot([x0, intersect_x], [y0, 0.4], pen=pg.mkPen('r', width=3))

            # Segmentul de sus
            plot.plot([intersect_x, x1], [0.4, y1], pen=pg.mkPen('g', width=3))
        else:
            # Dacă segmentul nu se intersectează cu y = 0.4, îl desenăm cu o singură culoare
            color = 'r' if y1 <= 0.4 else 'g'
            plot.plot([x0, x1], [y0, y1], pen=pg.mkPen(color, width=3))

    sys.exit(app.exec_())

if __name__ == "__main__":
    create_plot()
