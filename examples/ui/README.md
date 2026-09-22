# SCADA GUI example

Where `examples/main.cpp` is the DMS console example, this is the GUI
counterpart: a small Qt Widgets front end (mainwindow, table/config
editors, calibration/export windows) over the same DMS/Table data
layer.

The GUI's actual source lives at [gui/](../../gui/) -- a Qt Widgets
project with relative includes into `src/` (DMS, Table, the control
subsystem), so it isn't duplicated here.

Run it with either:

```sh
./run.sh          # from this directory
../../bin/scada   # or directly
```

Both build the app on first run (via `make gui` at the repo root,
which needs `qmake` from a Qt5 or Qt6 install) and then launch it.
