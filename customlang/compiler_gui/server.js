const express = require('express');
const { exec } = require('child_process');
const fs = require('fs');
const path = require('path');
const cors = require('cors');

const app = express();
app.use(cors());
app.use(express.json());
app.use(express.static('public'));

const COMPILER_DIR = path.join(__dirname, '..', 'compiler project');

app.post('/run', (req, res) => {
    const { code } = req.body;
    
    // Write code to input.txt
    const inputPath = path.join(COMPILER_DIR, 'input.txt');
    fs.writeFileSync(inputPath, code);

    // Run run.bat
    exec('cmd /c "run.bat < NUL"', { cwd: COMPILER_DIR }, (error, stdout, stderr) => {
        // Read the 7 phase outputs
        const phases = [
            'phase1_lexer.txt',
            'phase2_parser.txt',
            'phase3_semantic.txt',
            'phase4_tac.txt',
            'phase5_optimized.txt',
            'phase6_assembly.asm',
            'phase7_final_output.txt'
        ];

        const results = {};
        for (const phase of phases) {
            const p = path.join(COMPILER_DIR, phase);
            try {
                results[phase] = fs.readFileSync(p, 'utf8');
            } catch (err) {
                results[phase] = `Error reading ${phase} (it might not have been generated).`;
            }
        }
        
        results['console'] = stdout;
        results['error'] = stderr;

        res.json(results);
    });
});

const PORT = 3000;
app.listen(PORT, () => {
    console.log(`Server running at http://localhost:${PORT}`);
});
