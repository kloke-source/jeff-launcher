const {electron, app, BrowserWindow, globalShortcut, dialog} = require('electron')
const contents = require('electron').webContents

// Keep a global reference of the window object, if you don't, the window will
// be closed automatically when the JavaScript object is garbage collected.
let back
let searchBar
let miniBrowser
let miniPlayer

function createWindow () {
  // Create the browser window.
  back = new BrowserWindow({show: false})
  searchBar = new BrowserWindow({
    width: 800,
    height: 60,
    show:false,
    frame: false,
    parent: back,
    backgroundColor: "#212121"
  })
  miniBrowser = new BrowserWindow({
    width: 1000,
    height: 750,
    show: false,
    frame: false,
    parent: searchBar
  })
  miniPlayer = new BrowserWindow({
    width: 640,
    height: 380,
    x: 50,
    y: 50,
    alwaysOnTop: true,
    show: false,
    frame: false,
    parent: back
  })
  // Open the DevTools.
  searchBar.webContents.openDevTools()
  // miniPlayer.webContents.openDevTools()
  // miniBrowser.webContents.openDevTools()
  // back.webContents.openDevTools()

  // Emitted when the window is closed.
  back.on('closed', () => { back = null })
  searchBar.on('closed', () => { searchBar = null })
  miniBrowser.on('closed', () => { miniBrowser = null })
  miniPlayer.on('closed', () => {
    miniPlayer = null
    miniBrowser.show();

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
  globalShortcut.register('CmdOrCtrl+Q', function () {
    app.quit()
  })
    const electronScreen = require('electron').screen
    const size = electronScreen.getPrimaryDisplay().size
    var winWidth = parseInt((size.width)*0.55)
    back.setSize(winWidth, 60, false)
    back.setPosition((size.width/2) - winWidth/2, 0, false)
    back.loadURL(`file://${__dirname}/index.html`)
    searchBar.loadURL(`file://${__dirname}/searchbar.html`)
    miniBrowser.loadURL(`file://${__dirname}/index.html`)
})

youtube = false;

setInterval (function () {
  if (!youtube) {
    miniContents = contents.fromId(3)
    siteURL = miniContents.getURL()
    if (siteURL.indexOf('youtube.com/watch?') !== -1) {
      videoId = siteURL.slice(siteURL.indexOf("v=") + 2)
      miniPlayer.show()
      miniPlayer.loadURL(`file://${__dirname}/youtubeplayer.html`)
      youtube = true;
      webcont = contents.fromId(3)
      webcont.setAudioMuted(true)
      miniBrowser.hide()
    }
  }
}, 1000)

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
