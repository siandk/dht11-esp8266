import uvicorn

from datetime import datetime
from typing import Optional
from fastapi import FastAPI
from pymongo import MongoClient
from sensor import SensorReading

DATE_FORMAT = "%Y-%m-%dT%H:%M:%S"

app = FastAPI()
client = MongoClient('mongodb://localhost:27017')
db = client['sensor-data']


@app.get("/readings/add")
async def add_reading(value: float, sensor: str):
    db[sensor].insert_one({'time': datetime.now(), 'value': value})
    return 1

@app.get("/readings")
async def get_reading(sensor: str, date_from: Optional[datetime] = None, date_to: Optional[datetime] = None):
    query = {"time": {}} if date_from or date_to else {}
    if date_from:
        query["time"]["$gte"] = date_from
    if date_to:
        query["time"]["$lte"] = date_to
    result = []
    for reading in db[sensor].find(query):
        result.append(SensorReading(**reading))
    return result

if __name__ == "__main__":
    uvicorn.run("api:app", host="192.168.43.83", port=5000, reload=True, log_level="info", access_log=True)