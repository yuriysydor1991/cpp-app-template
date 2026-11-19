# The part the pipeline scripts share: they run at the project root and build
# in the BUILDDIR directory, writing the JUnit reports into its BDJUNITOUT
# subdirectory - the CI pipelines set both, a local run takes the defaults.

cd "$(dirname "$0")/../.."

BUILDDIR=${BUILDDIR:-build/pipeline}
BDJUNITOUT=${BDJUNITOUT:-junit-out}
