from setuptools import setup

setup(
    name='librosa',
    version='0.1.0',
    description='Python module for audio and music processing',
    author='Brian McFee',
    author_email='brm2132@columbia.edu',
    url='http://github.com/bmcfee/librosa',
    packages=['librosa'],
    long_description="""\
        Python module for audio and music processing.
    """,
    classifiers=[
          "License :: OSI Approved :: GNU General Public License (GPL)",
          "Programming Language :: Python",
          "Development Status :: 3 - Alpha",
          "Intended Audience :: Developers",
          "Topic :: Multimedia :: Sound/Audio :: Analysis",
    ],
    keywords='audio music sound',
    license='GPL',
    install_requires=[
        'audioread',
        'numpy >= 1.7.0',
        'scipy',
        'scikit-learn',
    ],
)
