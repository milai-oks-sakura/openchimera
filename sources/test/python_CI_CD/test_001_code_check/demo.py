"""
the demo about flake8 by using with python.

NOTE: https://www.osgeo.cn/flake8/user/python-api.html
"""
import argparse
from flake8.api import legacy as flake8


def main() -> None:
    """
    the inter function about this demo.
    """
    parser = argparse.ArgumentParser()

    parser.add_argument(
        "--check_path",
        type=str,
        default=None,
        help="the check path"
    )

    nsp = parser.parse_args()

    if nsp.check_path is None:
        return

    style_guide = flake8.get_style_guide()

    report = style_guide.check_files([nsp.check_path, ])

    if len(report.get_statistics('E')):
        raise RuntimeError("Flake8 found violations")

    return


if __name__ == "__main__":
    main()
