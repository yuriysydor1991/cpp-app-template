# The part the pipeline scripts share: they run at the project root and build
# in the BUILDDIR directory - the CI pipelines set it, a local run takes the
# default.

cd "$(dirname "$0")/../.."

BUILDDIR=${BUILDDIR:-build/pipeline}
