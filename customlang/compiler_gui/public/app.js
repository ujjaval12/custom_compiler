document.addEventListener('DOMContentLoaded', () => {
    const runBtn = document.getElementById('runBtn');
    const codeEditor = document.getElementById('codeEditor');
    const loader = document.getElementById('loader');
    const tabs = document.querySelectorAll('.tab');
    
    // Tab Switching Logic
    tabs.forEach(tab => {
        tab.addEventListener('click', () => {
            // Remove active from all tabs
            tabs.forEach(t => t.classList.remove('active'));
            document.querySelectorAll('.output-view').forEach(v => v.classList.remove('active'));
            
            // Add active to clicked tab
            tab.classList.add('active');
            const targetId = tab.getAttribute('data-target');
            document.getElementById(targetId).classList.add('active');
        });
    });

    // Run Button Logic
    runBtn.addEventListener('click', async () => {
        const code = codeEditor.value;
        
        // Show loader
        loader.classList.remove('hidden');
        runBtn.disabled = true;

        try {
            const response = await fetch('/run', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify({ code })
            });

            const data = await response.json();

            // Populate all tabs with data
            const phases = [
                'phase1_lexer.txt',
                'phase2_parser.txt',
                'phase3_semantic.txt',
                'phase4_tac.txt',
                'phase5_optimized.txt',
                'phase6_assembly.asm',
                'phase7_final_output.txt'
            ];

            phases.forEach(phase => {
                const el = document.getElementById(phase);
                if (el) {
                    el.textContent = data[phase] || 'No output.';
                }
            });

            // Populate console
            const consoleEl = document.getElementById('console');
            consoleEl.textContent = (data.console || '') + '\n' + (data.error || '');

            // Automatically switch to Final Output if there are no gross errors
            if (data['phase7_final_output.txt'] && !data['phase7_final_output.txt'].includes('Error reading')) {
                document.querySelector('[data-target="phase7_final_output.txt"]').click();
            } else {
                document.querySelector('[data-target="console"]').click();
            }

        } catch (error) {
            alert('Failed to connect to backend server. Make sure the Node server is running.');
        } finally {
            loader.classList.add('hidden');
            runBtn.disabled = false;
        }
    });
});
