import express from "express";
import db from "../db/conn.mjs";
import { ObjectId } from "mongodb";

const router = express.Router();

// -- Get a single runrecord
router.get("/", async (req, res) => {
    console.log("render index4");
    let collection = await db.collection("runrecords");

    const options = {
        // Sort returned documents in ascending order by title (A->Z)
        sort: { "BOR.Run number": -1 },
        limit: {$eq: 5}
    };
    let query = { };
    const result = await collection.find(query, options).limit(20).toArray();
    console.log(JSON.stringify(result));
    res.render('index', {'data': result});
});

// -- Get a single runrecord
router.get("/:id", async (req, res) => {
    let runno = parseInt(req.params.id);
    console.log("serving ... /rdb/" + req.params.id + " from " + req.ip);

    let collection = await db.collection("runrecords");

    let query = {"BOR.Run number": runno};
    let result = await collection.findOne(query);

    if (!result) res.send("Not found").status(404);
    else {
        console.log("calling singleRun with result: " + JSON.stringify(result));
        res.render('singleRun', {'data': result, 'runs': req.query.runs});
    }
});

export default router;