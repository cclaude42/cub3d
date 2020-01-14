const fs = require('fs')
const exec = require('child_process').execSync

require('C:/Web/dokustash/manager/globals.js')

const input = fs.readFileSync('input.tsv', 'utf-8').split('\n').slice(1).map(e => e.split('\t').map(f => f.trim()))
const stashFileData = JSON.parse(fs.readFileSync(stashDataDir + '/files.json', 'utf8'))
const stashFiles = Object.keys(stashFileData)

function propertiesFile(name, items, filename) {
  return [
    'type=item',
    `items=${items}`,
    `texture=./${filename}.png`,
    `nbt.display.Name=ipattern:${name}`
  ].join('\n')
}

input.forEach((item, i) => {
  if (item[0].length == 0 || item[1].length == 0 || item[2].length == 0 || item[4].length == 0) {
    console.log(`Skipping item #${i} because it is missing a required value. (${item.join(', ')})`)
    return
  }

  // Copy image file from the stash
  const filename = stashFiles.find(e => getID(e) == item[2])
  if (filename == null) {
    console.error(`ERROR: No file with ID ${item[2]}`)
    return
  }
  if (item[3].length >= 7) {
    if (!item[3].match(/\d+x\d+\+\d+\+\d+/)) {
      console.error(`ERROR: Invalid crop argument: ${item[3]}`)
      return
    }
    exec(`magick ${stash}/${filename} -crop ${item[3]} ${item[4]}.png`)
  } else {
    fs.copyFile(`${stash}/${filename}`, `${item[4]}.png`, (err) => { if (err) throw err })
  }

  // Create .properties file
  fs.writeFileSync(`${item[4]}.properties`, propertiesFile(item[0], item[1], item[4]))
})