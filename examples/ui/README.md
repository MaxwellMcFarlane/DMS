# SCADA GUI example

Where `examples/main.cpp` is the DMS console example, this is the GUI
counterpart: a small Qt Widgets front end (mainwindow, table/config
editors, calibration/export windows) over the same DMS/Table data
layer.

The GUI's actual source lives at
[legacy/scada_2017/scadagui/](../../legacy/scada_2017/scadagui/) --
it's 2017 Qt project code with relative includes into the rest of
`legacy/scada_2017/` (DMS, tools, ControlSubSystem), so it isn't
duplicated here.

Run it with either:

```sh
./run.sh          # from this directory
../../bin/scada   # or directly
```

Both build the app on first run (via `make gui` at the repo root,
which needs `qmake` from a Qt5 or Qt6 install) and then launch it.
