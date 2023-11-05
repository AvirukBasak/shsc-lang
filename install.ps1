# check if make, bison and gcc are installed
if (-not (Get-Command make -ErrorAction SilentlyContinue)) {
  Write-Host "install.ps1: error: make is not installed."
  exit 1
}

if (-not (Get-Command bison -ErrorAction SilentlyContinue)) {
  Write-Host "install.ps1: error: bison is not installed."
  exit 1
}

if (-not (Get-Command gcc -ErrorAction SilentlyContinue)) {
  Write-Host "install.ps1: error: gcc is not installed."
  exit 1
}

# run make
try {
  make
} catch {
  Write-Host "install.ps1: error: make failed."
  exit 1
}

# installation
Write-Host "`n-----------------------------------------------------`n"
Write-Host "To install run:"
Write-Host "make install"
Write-Host "`n-----------------------------------------------------`n"
