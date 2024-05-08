class Vector2
{
    constructor(x, y)
    {
        this.x = x
        this.y = y
    }
    distance(start, end)
    {
        return Math.sqrt(Math.pow(end.x - start.x, 2) + Math.pow(end.y - start.y, 2))
    }
    add(v)
    {
        this.x += v.x
        this.y += v.y
    }
    getSum(v)
    {
        return new Vector2(this.x + v.x, this.y + v.y)
    }
    sub(v)
    {
        this.x -= v.x
        this.y -= v.y
    }
    magnitude()
    {
        return Math.sqrt(Math.pow(this.x, 2) + Math.pow(this.y, 2))
    }
    delete()
    {
        delete this.x
        delete this.y
    }
}

class Tile
{
    constructor()
    {
        this.contentsID = -2 // -3, -2, -1 reserved for void, floor, and reserved respectively
    }

    getContentID()
    {
        return this.contentsID
    }
    setContentID(contents)
    {
        this.contentsID = contents
    }
}

class RoomManager
{
    constructor(width, height)
    {
        this.tiles = []
        for (var i = 0; i < width/100; i++)
        {
            tiles[i] = []
            for (var j = 0; j < height/100; j++)
            {
                tiles[i][j] = 0
            }
        }
    }

    loadMap(items)
    {
        for (var i = 0; i < items.len(); i++)
        {
            //console.log(items[i].)
        }
    }
}