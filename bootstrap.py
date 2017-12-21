import argparse
import os.path
import os
import re
import shutil
import subprocess
import winreg

ProgramOptions = None
DevEnvPath = None
MsBuildPath = None
QtSdkPath = None
BuildDir = None

def RunCommand(args, expected = 0):
	with subprocess.Popen(args, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT) as proc:
		for line in iter(proc.stdout.readline, b''):
			print('\t' + str(line.rstrip()))
		proc.communicate()
		print('')
		return proc.returncode == expected

def ResolvePath(path):
	path = os.path.abspath(path)
	if not os.path.exists(path):
		os.makedirs(path, 0o777, True)

	return path

def CopyFile(src, dst = None):
	filename = os.path.basename(src)

	if dst:
		dst = os.path.abspath(dst)
	else:
		dst = os.path.abspath(BuildDir + '/' + filename)

	ResolvePath(os.path.dirname(dst))

	if not os.path.exists(dst) or ProgramOptions.force:
		print('\tCopying "' + filename + "'...")
		shutil.copy(src, dst)

def SetupVSEnv():
	path = os.path.abspath(os.getenv('VS140COMNTOOLS') + '..\\..\\VC\\vcvarsall.bat')
	p = subprocess.Popen([path, 'amd64'], shell=True, stdout=subprocess.PIPE)
	stdout, stderr = p.communicate()

def ToolsVisualStudio():
	global DevEnvPath
	global MsBuildPath

	print('Visual Studio 2015:')

	DevEnvPath = os.path.abspath(os.getenv('VS140COMNTOOLS') + r'..\IDE\devenv.com')
	if not os.path.exists(DevEnvPath):
		print('\tCannot find Visual Studio executable.')

		return False

	print('\tINSTALLED')
	print('')

	print('MSBuild:')

	MsBuildPath = r'C:\Program Files (x86)\MSBuild\14.0\Bin\MSBuild.exe'
	if not os.path.exists(MsBuildPath):
		print('\tCannot find MSBuild executable for Visual Studio 2015.')

		return False

	print('\tINSTALLED')
	print('')

	return True

def ToolsQt():
	global QtSdkPath

	print('Qt:')

	if os.getenv('QT5SDKDIR') == None:
		print('\tEnvironment variable "QT5SDKDIR" must be set manually.')

		return False

	QtSdkPath = os.getenv('QT5SDKDIR')

	print('\tINSTALLED')
	print('')

	return True

def DependencyQt():
	print('Qt:')

	bin_dir = QtSdkPath + '/bin'

	qtlibs = [
		'Qt5Core',
	]
	for lib in qtlibs:
		CopyFile(bin_dir + '/' + lib + '.dll')
		CopyFile(bin_dir + '/' + lib + 'd.dll')

	print('\tINSTALLED')
	print('')

	return True

def GenerateSolution():
	solution_path = os.path.abspath('GlazedCake.sln')
	if os.path.exists(solution_path) and not ProgramOptions.force:
		print('\tSolution found.')
		print('')

		return True

	print('\tGenerating solution...')
	print('')

	SetupVSEnv()

	args = [ os.path.abspath(QtSdkPath + '/bin/qmake') ]
	args.extend(['-tp', 'vc'])
	args.extend(['-r', os.path.abspath('GlazedCake.pro')])
	args.extend(['-o', solution_path])

	if not RunCommand(args):
		print('\tFailed to generate solution for project.')

	return True

if __name__ == '__main__':
	parser = argparse.ArgumentParser(description='Bootstraps project and dependencies')
	parser.add_argument(
		'--force',
		dest = 'force',
		action = 'store_true',
		help = 'do not skip steps if they were already completed'
	)
	ProgramOptions = parser.parse_args()

	# globals

	BuildDir = ResolvePath('build')

	# tools

	print('[     TOOLS      ]')
	print('')

	if not ToolsVisualStudio():
		exit(1)

	if not ToolsQt():
		exit(1)

	# dependencies

	print('[  DEPENDENCIES  ]')
	print('')

	if not DependencyQt():
		exit(1)

	# project

	print('[    PROJECT     ]')
	print('')

	if not GenerateSolution():
		exit(1)

	print('[      DONE      ]')

	exit(0)