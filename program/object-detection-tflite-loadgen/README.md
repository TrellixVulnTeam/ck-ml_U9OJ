# MLPerf Inference v1.0 - Object Detection - TFLite (with Coral EdgeTPU support)

## Prerequisites

### Install Collective Knowledge (CK)

Please follow the [installation instructions](https://github.com/ctuning/ck#installation) for your system e.g.:

```bash
$ python3 -m pip install ck --user
$ echo "export PATH=$HOME/.local/bin:$PATH" >> ~/.bashrc
$ source ~/.bashrc && ck version
V1.15.0
```

### Pull [CK-ML](https://github.com/ctuning/ck-ml)

```bash
$ ck pull repo:ck-ml
```

### Pull [CK-Coral](https://github.com/ctuning/ck-coral)

To use the [Coral](https://coral.ai/) EdgeTPU accelerator:

```bash
$ ck pull repo:ck-coral
```

**NB:** Refresh all CK repositories after any updates (e.g. bug fixes):

```bash
$ ck pull all
```
