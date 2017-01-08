const {electron, app, BrowserWindow, globalShortcut, dialog} = require('electron')

// Keep a global reference of the window object, if you don't, the window will
// be closed automatically when the JavaScript object is garbage collected.
let back
let searchBar

function createWindow () {
  // Create the browser window.
  back = new BrowserWindow({show: false})
  searchBar = new BrowserWindow({
    width: 800,
    height: 50,
    show:false,
    frame: false,
    parent: back
  })

  // and load the index.html of the background window.
  back.loadURL(`file://${__dirname}/index.html`)
  searchBar.loadURL(`file://${__dirname}/searchbar.html`)

  // Open the DevTools.
  searchBar.webContents.openDevTools()
  // back.webContents.openDevTools()

  // Emitted when the window is closed.
  back.on('closed', () => {
    // Dereference the window object, usually you would store windows
    // in an array if your app supports multi windows, this is the time
    // when you should delete the corresponding element.
    back = null
  })
}

// This method will be called when Electron has finished
// initialization and is ready to create browser windows.
// Some APIs can only be used after this event occurs.
app.on('ready', createWindow)

// variable to toggle the show/hide of the search bar
var searchBarShow = false

// function to toggle the show or hide of the search bar
var searchBarToggle = function() {
  if (searchBarShow) {
    searchBar.hide()
  }
  else {
    searchBar.show()
  }
}

app.on('ready', function () {
  globalShortcut.register('CommandOrControl+Shift+Space', function () {
    searchBarToggle(searchBarShow)
    searchBarShow = !searchBarShow
  })
})

// Quit when all windows are closed.
app.on('window-all-closed', () => {
  // On macOS it is common for applications and their menu bar
  // to stay active until the user quits explicitly with Cmd + Q
  if (process.platform !== 'darwin') {
    app.quit()
  }
})

app.on('activate', () => {
  // On macOS it's common to re-create a window in the app when the
  // dock icon is clicked and there are no other windows open.
  if (back === null) {
    createWindow()
  }
})

// In this file you can include the rest of your app's specific main process
// code. You can also put them in separate files and require them here.
